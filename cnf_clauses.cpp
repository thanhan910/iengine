#include "cnf.h"

std::string convert_literal_node_to_string(Node* literal_node)
{
    if (literal_node->type == NOT)
    {
        return "~" + literal_node->children[0]->value;
    }

    else
    {
        return literal_node->value;
    }
}

Clause convert_clause_node_to_string_sets(Node* clause_node)
{
    if (clause_node->type == NOT || clause_node->type == SYMBOL)
    {
        std::string l = convert_literal_node_to_string(clause_node);

        return { l };
    }

    else
    {
        std::set<std::string> sequence;

        for (auto& literal_node : clause_node->children)
        {
            std::string l = convert_literal_node_to_string(literal_node);

            sequence.insert(l);
        }

        return sequence;
    }
}

std::vector<Clause> convert_root_node_to_clauses(Node* cnf_node)
{
    if (cnf_node->type == NOT || cnf_node->type == SYMBOL)
    {
        std::string l = convert_literal_node_to_string(cnf_node);

        return { { l } };
    }

    else if (cnf_node->type == OR)
    {
        Clause clause = convert_clause_node_to_string_sets(cnf_node);

        return { clause };
    }

    else
    {
        std::vector<Clause> clauses;

        for (auto& clause_node : cnf_node->children)
        {
            std::set<std::string> clause = convert_clause_node_to_string_sets(clause_node);

            clauses.push_back(clause);
        }

        return clauses;
    }
}




