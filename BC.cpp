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

    KB = parser.get_horn_clauses();

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
    for (const auto& clause : KB)
    {
        // Check if the consequent of the Horn clause matches the query
        if (clause.second == query)
        {
            bool result = true;

            // Try to prove each antecedent recursively
            for (const auto& antecedent : clause.first)
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
