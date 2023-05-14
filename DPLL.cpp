#include "DPLL.h"
#include "DPLL.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include "cnf.h"
#include "literal_symbols.h"

using namespace std;





// Function to get symbols from clauses
set<string> get_symbols(vector<set<string>>& cnf_clauses)
{
    set<string> result;

    for (const auto& clause : cnf_clauses)
    {
        for (const auto& lit : clause)
        {
            result.insert(atom(lit));
        }
    }

    return result;
}


// Function to find a pure symbol in the given set of symbols and clauses
pair<string, bool> find_pure_symbol(set<string>& symbols, vector<set<string>>& clauses, unordered_map<string, bool>& model)
{
    for (auto& symbol : symbols)
    {
        bool found_positive = false, found_negative = false;
        for (auto& clause : clauses)
        {
            if (clause.find(symbol) != clause.end())
            {
                found_positive = true;
            }
            if (clause.find("~" + symbol) != clause.end())
            {
                found_negative = true;
            }
        }
        if (found_positive && !found_negative)
        {
            return make_pair(symbol, true);
        }
        if (!found_positive && found_negative)
        {
            return make_pair(symbol, false);
        }
    }
    return make_pair("", false);
}



// Main DPLL algorithm function
bool dpll(vector<set<string>> clauses, set<string> symbols, unordered_map<string, bool> model)
{
    bool all_clauses_true = true;

    unordered_map<string, bool> is_pure;

    unordered_map<string, bool> symbol_value;

    for (auto& clause : clauses)
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

    unordered_map<string, bool> model_true = model;
    model_true[next_symbol] = true;

    unordered_map<string, bool> model_false = model;
    model_false[next_symbol] = false;

    return dpll(clauses, symbols, model_true) || dpll(clauses, symbols, model_false);
}

// Wrapper function to call the DPLL algorithm
bool dpll_satisfiable(string& sentence)
{
    vector<set<string>> clauses = cnf(sentence);

    set<string> symbols = get_symbols(clauses);

    unordered_map<string, bool> model;

    return dpll(clauses, symbols, model);
}

bool dpll_prove(string& KB, string& query)
{
    string sentence = KB + "~(" + query + ");";

    return !dpll_satisfiable(sentence);
}





