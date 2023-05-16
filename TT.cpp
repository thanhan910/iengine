#include "TT.h"
#include "Parser.h"
#include "Model.h"
#include "print_node.h"
#include <unordered_map>
#include <set>



TT::TT(std::string& kb_, std::string& query_) :
	model_count(0)
{
    Parser parser_kb(kb_);
    Parser parser_query(query_);

    KB = parser_kb.get_tree();
	query = parser_query.get_tree();

    // Get a list of all unique symbols in the knowledge base and the query symbol
    std::set<std::string> symbols_set_kb = parser_kb.get_symbols();
    std::set<std::string> symbols_set_query = parser_query.get_symbols();

    for (auto& s : symbols_set_kb)
    {
        symbols_set.insert(s);
    }

    for (auto& s : symbols_set_query)
    {
        symbols_set.insert(s);
    }
}

bool TT::check()
{
    // Transform the set of symbols into a stack
    std::vector<std::string> symbols(symbols_set.begin(), symbols_set.end());

    // Create a map to store the truth values of each symbol in the knowledge base and the query symbol
    std::unordered_map<std::string, bool> model;

    return check_all(symbols, model);
}

bool TT::check_all(std::vector<std::string> symbols, std::unordered_map<std::string, bool> model)
{
    if (symbols.empty())
    {
        if (pl_value(model, KB) == 1)
        {
            int kb_entails_query = pl_value(model, query);

            if (kb_entails_query == 1)
            {
                model_count++;
                true_models.push_back(model);
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

