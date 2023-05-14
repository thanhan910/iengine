#include "BC.h"

#include "Node.h"
#include "Model.h"
#include "ParseTree.h"
#include "Lexer.h"

#include <unordered_map>
#include <queue>
#include <iostream>
#include <set>

std::set<std::string> GetAntecedents(Node* horn_node)
{
    if (horn_node->type == VARIABLE)
    {
        return std::set<std::string>();
    }

    else if (horn_node->type == IMPLIES)
    {
        return get_symbols(horn_node->children[0]);
    }

    else
    {
        std::cerr << "Node is not in horn form\n";
        exit(1);
    }
}

std::string GetConsequent(Node* horn_node)
{
    if (horn_node->type == VARIABLE)
    {
        return horn_node->value;
    }

    else if (horn_node->type == IMPLIES)
    {
        return horn_node->children[1]->value;
    }

    else
    {
        std::cerr << "Node is not in horn form\n";
        exit(1);
    }
}

BC::BC(std::string& kb_, std::string& query_) :
    query(query_)
{
    ParseTree tree_kb(Lexer(kb_).fToken);
    tree_kb.parse();
    kb = tree_kb.root_node;
}

bool BC::check()
{
    return ask(query);
}


bool BC::ask(const std::string& query)
{
    // Check if the query is already a fact
    if (facts.find(query) != facts.end())
    {
        return facts[query];
    }

    // Try to prove the query using backward chaining
    for (const auto& clause : kb->children)
    {
        // Check if the consequent of the Horn clause matches the query
        if (GetConsequent(clause) == query)
        {
            bool result = true;

            // Try to prove each antecedent recursively
            for (const auto& antecedent : GetAntecedents(clause))
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
