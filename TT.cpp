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
    int pl_kb = pl_value(model, KB);

    if (pl_kb == 1)
    {
        models.push_back(model);

        int pl_query = pl_value(model, query);

        if (pl_query == 1)
        {
            model_count += (size_t)pow(2, symbols.size());
            return true;
        }

        else if (pl_query == 0)
        {
            return false;
        }
    }

    else if(pl_kb == 0)
    {
        return true;
    }

    // else, if pl_kb == 2 or (pl_query == 2 and pl_kb == 1)
    // then that means there are still symbols to assign

    std::string p = symbols.back();
    symbols.pop_back();

    model[p] = true;
    if (!check_all(symbols, model)) return false;

    model[p] = false;
    if (!check_all(symbols, model)) return false;

    return true;
}

void TT::print_result()
{
    if (kb_entails_query)
    {
        std::cout << "YES: " << model_count << '\n';
    }

    else
    {
        std::cout << "NO\n";
    }

    /*for (size_t i=0; i< models.size(); i++)
    {
        if (i == 0)
        {
            print_model(models[i], false, true);
        }

        else
        {
            print_model(models[i], false, true);
        }
        std::cout << '\n';
    }*/
}
