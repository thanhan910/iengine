#include "BC.h"

#include "Node.h"
#include "Model.h"
#include "Parser.h"

#include <unordered_map>
#include <queue>
#include <iostream>
#include <set>


BC::BC(std::string& KB_, std::string& query_) :
    IE(KB_, query_)
{
    Parser parser(KB_);

    clauses = parser.get_horn_clauses();

    is_checking = std::vector<bool>(clauses.size(), false);

    kb_entails_query = ask(query_);
}

bool BC::ask(const std::string& query)
{
    // Check if the query is already a fact
    if (facts.find(query) != facts.end())
    {
        return facts[query];
    }

    // Try to prove the query using backward chaining
    for (size_t i=0; i < clauses.size(); i++)
    {
        
        // Check if the consequent of the Horn clause matches the query
        // and if the clause is not being checked already to avoid infinite loop
        if (clauses[i].second == query && !is_checking[i])
        {
            is_checking[i] = true;

            bool result = true;

            // Try to prove each antecedent recursively
            for (const auto& antecedent : clauses[i].first)
            {
                result &= ask(antecedent);
            }

            // If all antecedents are true, the consequent is also true
            if (result)
            {
                sequence.push_back(query);
                facts[query] = true;
                return true;
            }
        }
    }

    // If the query cannot be proved, it is false
    facts[query] = false;
    return false;
}

void BC::print_result()
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
