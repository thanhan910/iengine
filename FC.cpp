#include "FC.h"
#include <unordered_map>
#include "Node.h"
#include <queue>
#include <iostream>
#include "Model.h"
#include "Parser.h"

FC::FC(std::string& kb_, std::string& query_) :
    IE(kb_, query_)
{
    kb_entails_query = check(kb_, query_);
}

void FC::print_result()
{
    if (kb_entails_query)
    {
        std::cout << "YES:";

        for (size_t i = 0; i < sequence.size(); i++)
        {
            std::cout << " " << sequence[i];

            if (i < sequence.size() - 1)
            {
                std::cout << ",";
            }
        }
    }

    else
    {
        std::cout << "NO\n";
    }

    std::cout << "\n";
}


// Main check function
bool FC::check(std::string& kb, std::string& query)
{
    Parser parser(kb);
    
    std::set<std::string> symbols = parser.get_symbols();

    // Initialize inferred symbols to false

    std::unordered_map<std::string, bool> inferred;

    for (auto& symbol : symbols)
    {
        inferred[symbol] = false;
    }

    // Initialize agenda queue and count map

    std::queue<std::string> agenda; 

    std::vector<HornClause> clauses = parser.get_horn_clauses();

    std::vector<size_t> count; // the number of literals in antedecent that is not yet inferred

    for (size_t i = 0; i < clauses.size(); i++)
    {
        count.push_back(clauses[i].first.size());

        if (clauses[i].first.size() == 0)
        {
            agenda.push(clauses[i].second);
        }
    }

    // Iterate until agenda is empty
    while (!agenda.empty())
    {
        std::string symbol = agenda.front();
        agenda.pop();

        if (inferred[symbol]) continue;

        sequence.push_back(symbol);

        // If the symbol is the query symbol, return true
        if (symbol == query)
        {
            sequence.push_back(symbol);
            return true;
        }

        inferred[symbol] = true;

        // Infer the symbol's truth value
        for (size_t i = 0; i < clauses.size(); i++)
        {
            // Optimization: Skip the horn clauses with all literals in antedecents already inferred
            if (count[i] == 0) continue;

            // for each Horn clause c in whose premise p appears do
            if (clauses[i].first.count(symbol))
            {
                count[i]--;

                if (count[i] == 0)
                {
                    if (clauses[i].second == query)
                    {
                        sequence.push_back(query);
                        return true;
                    }
                    agenda.push(clauses[i].second);
                }
            }
        }
    }

    return false;
}


