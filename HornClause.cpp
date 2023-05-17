#include "HornClause.h"
#include "Literal.h"


// Convert Horn form node to a HornClause object
HornClause convert_horn_node_to_horn_object(Node* horn_node)
{
    if (horn_node->type == SYMBOL || horn_node->type == NOT)
    {
        return { {}, convert_literal_node_to_string(horn_node) };
    }

    else // if (horn_node->type == IMPLIES)
    {
        std::string consequent = convert_literal_node_to_string(horn_node->children[1]);

        std::set<std::string> antedecent;

        Node* left_node = horn_node->children[0];

        if (left_node->type == SYMBOL || left_node->type == NOT)
        {
            antedecent = { convert_literal_node_to_string(left_node) };
        }
        else // if (left_node->type == AND)
        {

            for (Node* lit : left_node->children)
            {
                antedecent.insert(convert_literal_node_to_string(lit));
            }
        }

        return { antedecent, consequent };
    }
}

// Convert a Horn form tree to a vector of Horn Clauses
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
