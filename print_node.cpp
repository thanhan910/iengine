#include "print_node.h"
#include <iostream>
//#define TREE_STYLE
//#define PAREN_STYLE
#define BRACKET_STYLE

void print_node(Node* node, std::string prefix, std::string child_prefix)
{
    if (node == nullptr)
    {
        return;
    }

#ifdef TREE_STYLE

    std::cout << prefix << node->value << std::endl;

    for (size_t i = 0; i < node->children.size(); i++)
    {
        Node* child = node->children[i];

        std::string grandchild_prefix = child_prefix + (i == node->children.size() - 1 ? "    " : ":   ");

        std::cout << child_prefix << ":\n";

        print_node(child, child_prefix + ":...", grandchild_prefix);
    }
#endif
#ifdef PAREN_STYLE

    std::cout << node->value;

    for (int i = 0; i < node->children.size(); i++)
    {
        if (i == 0 && node->children.size() > 1)
        {
            std::cout << "( ";
        }
        print_node(node->children[i]);
        if (i < node->children.size() - 1)
        {
            std::cout << ", ";
        }
        else if (node->children.size() > 1)
        {
            std::cout << " )";
        }
    }
#endif

#ifdef BRACKET_STYLE

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
            print_node(child->children[i], prefix + ":  ");
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
        print_node(node->children[i], prefix + ":  ");
    }

    std::cout << prefix << "}\n";
#endif


}