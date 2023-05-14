#include "TT.h"
#include "Lexer.h"
#include "ParseTree.h"
#include "Model.h"

#include <unordered_map>
#include <set>
#include "print_node.h"


TT::TT(std::string& kb_, std::string& query_) :
	model_count(0)
{
	ParseTree tree_kb(Lexer(kb_).fToken);
	tree_kb.parse();
    kb = tree_kb.root_node;

	ParseTree tree_query(Lexer(query_).fToken);
	tree_query.parse();
	query = tree_query.root_node;
}

bool TT::check()
{
    // Get a list of all unique symbols in the knowledge base and the query symbol
    std::set<std::string> symbols_set_kb = get_symbols(kb);
    std::set<std::string> symbols_set_query = get_symbols(query);

    std::set<std::string> symbols_set;

    for (auto& s : symbols_set_kb)
    {
        symbols_set.insert(s);
    }

    for (auto& s : symbols_set_query)
    {
        symbols_set.insert(s);
    }

    std::vector<std::string> symbols(symbols_set.begin(), symbols_set.end());

    // Create a map to store the truth values of each symbol in the knowledge base and the query symbol
    std::unordered_map<std::string, bool> model;

    return check_all(symbols, model);
}

bool TT::check_all(std::vector<std::string> symbols, std::unordered_map<std::string, bool> model)
{
    if (symbols.empty())
    {
        if (pl_true(model, kb) == 1)
        {
            int kb_entails_query = pl_true(model, query);

            if (kb_entails_query == 1)
            {
                ++model_count;
                return true;
            }

            else
            {
                return false;
            }
        }

        else
        {
            return true;
        }
    }

    else
    {
        std::string p = symbols.back();
        symbols.pop_back();

        std::unordered_map<std::string, bool> model_true = model;
        std::unordered_map<std::string, bool> model_false = model;
        model_true[p] = true;
        model_false[p] = false;
        return check_all(symbols, model_true) && check_all(symbols, model_false);
    }
}

