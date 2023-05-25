#include "Literal.h"

// Function to check if literal is a negation of a symbol or not
bool is_negation(const std::string& literal)
{
    return !literal.empty() && literal[0] == '~';
}

// Function to get the reverse of literal
std::string reverse(const std::string& literal)
{
    if (is_negation(literal))
    {
        return literal.substr(1, std::string::npos);
    }
    else
    {
        return "~" + literal;
    }
}


// Function to get symbol from literal
std::string get_symbol(const std::string& literal)
{
    if (is_negation(literal))
    {
        return literal.substr(1, std::string::npos);
    }
    else
    {
        return literal;
    }
}

// Check if a Node is a literal
bool is_literal(Node* node)
{
    return node->type == SYMBOL || (node->type == NOT && node->children.size() == 1 && node->children[0]->type == SYMBOL);
}

// Convert literal-type node to string
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

