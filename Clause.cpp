#include "Clause.h"
#include "Literal.h"
#include <iostream>

bool is_tautology(Clause clause)
{
    std::set<std::string> symbols;

    for (auto& lit : clause)
    {
        std::string s = get_symbol(lit);
        if (symbols.count(s)) // Since Clause is a set, a symbol can only appear at most twice in the Clause set
        {
            return true;
        }
        symbols.insert(s);
    }

    return false;
}


// Convert a clause-type node to a set of strings
Clause convert_clause_node_to_set(Node* clause_node)
{
    if (is_literal(clause_node))
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
        Clause clause = convert_clause_node_to_set(cnf_node);
        if (is_tautology(clause))
        {
            return { { } };
        }
        else
        {
            return { clause };
        }
    }

    else
    {
        std::vector<Clause> clauses;

        for (auto& clause_node : cnf_node->children)
        {
            Clause clause = convert_clause_node_to_set(clause_node);

            if (!is_tautology(clause))
            {
                clauses.push_back(convert_clause_node_to_set(clause_node));
            }
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





