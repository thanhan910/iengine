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




// Main DPLL algorithm function
bool dpll(vector<Clause> clauses, set<string> symbols, Model model)
{

    // Simultaneously perform unit propagation, pure literal elimination, and check the pl value of the sentence
    bool all_clauses_true = true; // If there is one false or indeterminate clause, then not all clauses are true

    // Track the pure symbols for pure literal elimination
    unordered_map<string, bool> symbol_value; // This map just track the value of the symbol in the first occurence
    unordered_map<string, bool> is_pure; // If the symbol already exists in symbol_value but it's value is different, then it is not pure

    // Iterate over all clauses
    for (auto& clause : clauses)
    {
        // Track if the clause is true or false or indeterminate
        bool clause_true = false; // If there is a true literal, then the clause is true
        bool clause_false = true; // If all literals are false, then the clause is false

        // Track unit symbols
        // If the literal is the only literal in the clause that is not assigned any value, then that is a unit literal
        string unassigned_symbol = ""; // Record the unassigned literal's symbol 
        bool unassigned_value = false; // Record the unassigned symbol's value
        size_t unassigned_literal_count = clause.size(); // Count the number of unassigned literals in the 

        // Iterate over all literals in the clause
        for (auto& lit : clause)
        {
            string symbol = atom(lit); 
            bool value = !is_negation(lit);

            if (model.count(symbol))
            {
                unassigned_literal_count--;

                if (value == model[symbol])
                {
                    clause_true = true;
                    clause_false = false;
                    break;
                }
            }

            else // when the symbol is not in the model
            {
                clause_false = false;

                unassigned_symbol = symbol; unassigned_value = value;

                if (is_pure.find(symbol) != is_pure.end())
                {
                    is_pure[symbol] = false;
                }
                else
                {
                    symbol_value[symbol] = value;
                    is_pure[symbol] = true; // temporary make it true when only one occurence of the symbol is found
                }
            }
        }

        if (!clause_true)
        {
            all_clauses_true = false;

            if (unassigned_symbol != "" && unassigned_literal_count == 1)
            {
                // Unit literal found
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

    // Find and eliminate (assign values to) pure symbols
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

    // If all symbols are assigned values, return false
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





