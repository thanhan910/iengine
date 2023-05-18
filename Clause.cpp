#include "Clause.h"
#include "Literal.h"
#include <iostream>


// Convert a clause-type node to a set of strings
Clause convert_clause_node_to_set(Node* clause_node)
{
    if (clause_node->type == NOT || clause_node->type == SYMBOL)
    {
        return { convert_literal_node_to_string(clause_node) };
    }

    else
    {
        Clause clause;

        for (auto& literal_node : clause_node->children)
        {
            clause.insert(convert_literal_node_to_string(literal_node));
        }

        return clause;
    }
}

// Convert tree in CNF form to list of clauses
std::vector<Clause> convert_root_node_to_clauses(Node* cnf_node)
{
    if (cnf_node->type == NOT || cnf_node->type == SYMBOL)
    {
        std::string l = convert_literal_node_to_string(cnf_node);

        return { { l } };
    }

    else if (cnf_node->type == OR)
    {
        return { convert_clause_node_to_set(cnf_node) };
    }

    else
    {
        std::vector<Clause> clauses;

        for (auto& clause_node : cnf_node->children)
        {
            clauses.push_back(convert_clause_node_to_set(clause_node));
        }

        return clauses;
    }
}

void print_clause(Clause& clause, std::string delimiter, std::string left, std::string right)
{
    std::cout << left;

    for (auto it = clause.begin(); it != clause.end(); ++it)
    {
        std::cout << *it;  // Print the element

        // Print '|' separator if it's not the last element
        if (std::next(it) != clause.end())
        {
            std::cout << delimiter;
        }
    }

    std::cout << right;
}





