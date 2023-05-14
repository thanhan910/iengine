#include "literal_symbols.h"

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
std::string atom(const std::string& literal)
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