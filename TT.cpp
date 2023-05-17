#include "TT.h"
#include "Parser.h"
#include "Model.h"
#include "print_node.h"
#include <iostream>

TT::TT(std::string& kb_, std::string& query_) :
	IE(kb_, query_), 
    model_count(0)
{
    Parser parser_kb(kb_);
    Parser parser_query(query_);

    KB = parser_kb.get_tree();
	query = parser_query.get_tree();

    // Get a set of all unique symbols in the knowledge base and the query symbol
    std::set<std::string> symbols_set_kb = parser_kb.get_symbols();
    std::set<std::string> symbols_set_query = parser_query.get_symbols();
    std::set<std::string> symbols_set;
    for (auto& s : symbols_set_kb) symbols_set.insert(s);
    for (auto& s : symbols_set_query) symbols_set.insert(s);

    // Transform the set of symbols into a stack
    std::vector<std::string> symbols(symbols_set.rbegin(), symbols_set.rend());

    // Create a map to store the truth values of each symbol in the knowledge base and the query symbol
    Model model;

    kb_entails_query = check_all(symbols, model);
}

// Backtrack: Recursively construct the model then check the logic value of kb and query
bool TT::check_all(std::vector<std::string> symbols, Model model)
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

        else
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

void TT::print_result()
{
    if (kb_entails_query)
    {
        std::cout << "YES: " << model_count;
    }

    else
    {
        std::cout << "NO";
    }

    std::cout << '\n';
}
