#include "HornClause.h"

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



HornClause convert_horn_node_to_horn_object(Node* horn_node)
{
    if (horn_node->type == SYMBOL || horn_node->type == NOT)
    {
        return { {}, convert_literal_node_to_string(horn_node) };
    }

    else // if (horn_node->type == IMPLIES)
    {
        std::vector<std::string> antedecents;

        std::string consequent;

        std::string consequent = convert_literal_node_to_string(horn_node->children[1]);

        Node* left_node = horn_node->children[0];

        if (left_node->type == SYMBOL || left_node->type == NOT)
        {
            antedecents = { convert_literal_node_to_string(left_node) };
        }
        else // if (conj_node->type == AND)
        {

            for (Node* lit : left_node->children)
            {
                antedecents.push_back(convert_literal_node_to_string(lit));
            }
        }

        return { antedecents, consequent };
    }
}


std::vector<HornClause> convert_root_node_to_horn_clauses(Node* root)
{
    if (root->type == NOT || root->type == SYMBOL || root->type == IMPLIES)
    {
        return { convert_horn_node_to_horn_object(root) };
    }

    else
    {
        std::vector<HornClause> clauses;

        for (Node* horn_node : root->children)
        {
            clauses.push_back(convert_horn_node_to_horn_object(horn_node));
        }

        return clauses;
    }
}
