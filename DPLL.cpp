#include "DPLL.h"
#include "Parser.h"
#include "Literal.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

DPLL::DPLL(std::string& KB_, std::string& query_) :
    IE(KB_, query_)
{
    string sentence = KB_ + "~(" + query_ + ");";

    Parser parser(sentence);
    
    clauses = parser.get_cnf_clauses();

    clause_is_true = vector<bool>(clauses.size(), false);

    set<string> symbols = parser.get_symbols();

    Model model;

    kb_entails_query = !dpll(symbols, model);
}

// Main DPLL algorithm function
bool DPLL::dpll(std::set<std::string> symbols, Model model)
{
    // Simultaneously perform unit propagation, pure literal elimination, and check the pl value of the sentence
    bool all_clauses_true = true; // If there is one false or indeterminate clause, then not all clauses are true

    // Track the pure symbols for pure literal elimination
    unordered_map<string, bool> symbol_value; // This map just track the value of the symbol in the first occurence
    unordered_map<string, bool> is_pure; // If the symbol already exists in symbol_value but it's value is different, then it is not pure

    // Iterate over all clauses
    for (size_t i = 0; i < clauses.size(); i++)
    {
        // Skip true clauses
        if (clause_is_true[i]) continue;

        Clause& clause = clauses[i];

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
            string symbol = get_symbol(lit);
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

                if (symbol_value.count(symbol) && symbol_value[symbol] != value)
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

        if (clause_true)
        {
            clause_is_true[i] = true;
            sequence.emplace_back(clause, "", true);
        }

        else
        {
            all_clauses_true = false;

            if (unassigned_symbol != "" && unassigned_literal_count == 1)
            {
                // Unit literal found
                symbols.erase(unassigned_symbol);
                model[unassigned_symbol] = unassigned_value;
                sequence.emplace_back(clause, unassigned_symbol, unassigned_value);
                return dpll(symbols, model);
            }
        }

        if (clause_false)
        {
            sequence.emplace_back(clause, "", false);
            return false;
        }
    }

    if (all_clauses_true) return true;

    // Find and eliminate (assign values to) pure symbols
    bool pure_symbol_exist = false;
    for (auto& symbol : is_pure)
    {
        if (symbol.second)
        {
            pure_symbol_exist = true;
            symbols.erase(symbol.first);
            model[symbol.first] = symbol_value[symbol.first];
            sequence.emplace_back(Clause{}, symbol.first, symbol.second);
        }
    }
    if (pure_symbol_exist)
    {
        return dpll(symbols, model);
    }

    // If all symbols are assigned values, return false
    if (symbols.empty())
    {
        return false;
    }

    string next_symbol = *(symbols.begin());
    symbols.erase(next_symbol);

    model[next_symbol] = true;
    if (dpll(symbols, model)) return true;

    model[next_symbol] = false;
    if (dpll(symbols, model)) return true;

    return false;
}

void DPLL::print_result()
{
    if (kb_entails_query)
    {
        cout << "YES\n";

        cout << "KB & ~query in CNF form:\n";
        for (Clause clause : clauses)
        {
            print_clause(clause, " ", "{ ", " }");
            cout << "; ";
        }
        cout << endl;

        cout << "DPLL sequence:\n";

        for (auto& entry : sequence)
        {
            Clause clause = get<0>(entry);
            string symbol = get<1>(entry);
            bool value = get<2>(entry);
            if (clause.size() > 0)
            {
                print_clause(clause, " ", "{ ", " }");

                if (symbol == "")
                {
                    cout << " = " << (value ? "true" : "false");
                }
                else
                {
                    cout << " => [ ";
                    cout << symbol << " = " << (value ? "true" : "false") << " ]";
                }
            }
            else if (symbol != "")
            {
                cout << symbol << " = " << (value ? "true" : "false");
            }

            cout << endl;
        }
    }

    else
    {
        cout << "NO\n";
    }
}