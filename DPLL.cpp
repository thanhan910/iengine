#include "DPLL.h"
#include "Parser.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include "literal_symbols.h"
#include "Model.h"

using namespace std;


typedef set<string> Clause;


// Main DPLL algorithm function
bool dpll(vector<Clause> clauses, set<string> symbols, Model model)
{
    bool all_clauses_true = true;

    unordered_map<string, bool> is_pure;

    unordered_map<string, bool> symbol_value;

    for (Clause& clause : clauses)
    {
        bool clause_true = false;

        bool clause_false = true;

        string unassigned_symbol = "";

        bool unassigned_value = false;

        size_t unassigned_literal_count = clause.size();

        for (auto& literal : clause)
        {
            string symbol = atom(literal);
            bool value = !is_negation(literal);

            if (model.find(symbol) != model.end())
            {
                if (model[symbol] == value)
                {
                    clause_true = true;
                    clause_false = false;
                    break;
                }

                else
                {
                    unassigned_literal_count--;
                }
            }

            else
            {
                clause_false = false;

                if (unassigned_symbol == "")
                {
                    unassigned_symbol = symbol;
                    unassigned_value = value;
                }

                if (is_pure.find(symbol) != is_pure.end())
                {
                    is_pure[symbol] = false;
                }
                else
                {
                    is_pure[symbol] = true;
                    symbol_value[symbol] = value;
                }
            }
        }

        if (!clause_true)
        {
            all_clauses_true = false;

            if (unassigned_symbol != "" && unassigned_literal_count == 1)
            {
                symbols.erase(unassigned_symbol);
                model[unassigned_symbol] = unassigned_value;
                return dpll(clauses, symbols, model);
            }
        }

        if (clause_false)
        {
            return false;
        }
    }

    if (all_clauses_true)
    {
        return true;
    }

    // Find pure symbols

    bool pure_symbol_exist = false;

    for (auto& symbol : is_pure)
    {
        if (symbol.second)
        {
            pure_symbol_exist = true;

            symbols.erase(symbol.first);

            model[symbol.first] = symbol_value[symbol.first];

        }
    }

    if (pure_symbol_exist)
    {
        return dpll(clauses, symbols, model);
    }

    if (symbols.empty())
    {
        return false;
    }

    string next_symbol = *(symbols.begin());
    symbols.erase(next_symbol);

    model[next_symbol] = true;
    if (dpll(clauses, symbols, model)) return true;

    model[next_symbol] = false;
    if (dpll(clauses, symbols, model)) return true;

    return false;
}

// Wrapper function to call the DPLL algorithm
bool dpll_satisfiable(string& sentence)
{
    Parser parser(sentence);

    vector<Clause> clauses = parser.get_cnf_clauses();

    set<string> symbols = parser.get_symbols();

    Model model;

    return dpll(clauses, symbols, model);
}

bool dpll_prove(string& KB, string& query)
{
    string sentence = KB + "~(" + query + ");";

    return !dpll_satisfiable(sentence);
}





