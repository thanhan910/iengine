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
    std::vector<std::string> symbols(symbols_set.rbegin(), symbols_set.rend());

    // Create a map to store the truth values of each symbol in the knowledge base and the query symbol
    std::unordered_map<std::string, bool> model;

    return check_all(symbols, model);
}

bool TT::check_all(std::vector<std::string> symbols, std::unordered_map<std::string, bool> model)
{
    if (symbols.empty())
    {
        int pl_kb = pl_value(model, KB);
        int pl_query = pl_value(model, query);

        if (pl_kb == 1)
        {
            if (pl_query == 1)
            {
                model_count++;
                return true;
            }

            else
            {
                return false;
            }
        }

        else if (pl_kb == 0)
        {
            return true;
        }
    }

    else
    {
        std::string p = symbols.back();
        symbols.pop_back();

        model[p] = true;
        if (!check_all(symbols, model)) return false;

        model[p] = false;
        if (!check_all(symbols, model)) return false;

        return true;
    }
}

