#include "print_node.h"
#include "Literal.h"
#include <iostream>

void print_node_tree_style(Node* node, std::string prefix, std::string child_prefix)
{
    if (node == nullptr) return;

    std::cout << prefix << node->value << std::endl;

    for (size_t i = 0; i < node->children.size(); i++)
    {
        Node* child = node->children[i];

        std::string grandchild_prefix = child_prefix + (i == node->children.size() - 1 ? "    " : ":   ");

        std::cout << child_prefix << ":\n";

        print_node_tree_style(child, child_prefix + ":...", grandchild_prefix);
    }
}

void print_node_parentheses_style(Node* node)
{
    if (node == nullptr) return;

    std::cout << node->value;

    for (int i = 0; i < node->children.size(); i++)
    {
        if (i == 0 && (node->children.size() > 1 || !is_literal(node)))
        {
            std::cout << "( ";
        }
        
        print_node_parentheses_style(node->children[i]);

        if (i < node->children.size() - 1)
        {
            std::cout << ", ";
        }
        else if (node->children.size() > 1 || !is_literal(node))
        {
            std::cout << " )";
        }
    }
}

void print_node_bracket_style(Node* node, std::string prefix)
{
    if (node == nullptr) return;

    if (node->type == TokenType::NOT)
    {
        Node* child = node->children[0];

        std::cout << prefix << node->value << " " << child->value;

        if (child->children.size() == 0)
        {
            std::cout << ";\n";
            return;
        }

        else
        {
            std::cout << " {\n";
        }


        for (int i = 0; i < child->children.size(); i++)
        {
            print_node_bracket_style(child->children[i], prefix + ":  ");
        }

        std::cout << prefix << "}\n";

        return;
    }

    std::cout << prefix << node->value;

    if (node->children.size() == 0)
    {
        std::cout << ";\n";
        return;
    }

    else
    {
        std::cout << " {\n";
    }

    for (int i = 0; i < node->children.size(); i++)
    {
        print_node_bracket_style(node->children[i], prefix + ":  ");
    }

    std::cout << prefix << "}\n";
}

void print_node_infix(Node* node)
{
    if (node == nullptr) return;

    if (is_literal(node))
    {
        std::cout << convert_literal_node_to_string(node);
        return;
    }

    std::cout << "( ";

    for (int i = 0; i < node->children.size(); i++)
    {
        if (i > 0)
        {
            std::cout << " " << node->value << " ";
        }
        print_node_infix(node->children[i]);
    }

    std::cout << " )";
}
