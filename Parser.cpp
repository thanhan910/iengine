#include "Parser.h"
#include "ParseTree.h"
#include "cnf.h"
#include "Clause.h"
#include <iostream>

Parser::Parser(std::string& input_) :
    input(input_),
    root(nullptr),
    tokenized(false),
    tree_created(false),
    converted_to_cnf(false)
{ }



// Define a function to tokenize the input
void Parser::tokenize()
{
    tokenized = true;

    size_t pos = 0;

    while (pos < input.size())
    {
        // Skip white spaces
        if (isspace(input[pos]))
        {
            pos++;
            continue;
        }

        // Check if currently considered string is a special keyword

        size_t keyword_found_size = 0;

        for (const auto& keyword_token : KEYWORDS)
        {
            TokenType type = keyword_token.first;

            std::string keyword = keyword_token.second;

            if (input.substr(pos, keyword.size()) == keyword)
            {
                keyword_found_size = keyword.size();

                tokens.emplace_back(type, keyword);

                pos += keyword_found_size;

                break;
            }
        }

        if (keyword_found_size > 0)
        {
            continue;
        }

        // Check if currently considered string is a variable/symbol

        if (isalpha(input[pos]) || input[pos] == '_')
        {
            // Parse a variable
            size_t end = pos + 1;
            while (end < input.size() && (isalnum(input[end]) || input[end] == '_'))
            {
                end++;
            }
            std::string var = input.substr(pos, end - pos);
            tokens.emplace_back(SYMBOL, var);
            symbols.insert(var);
            pos = end;

            continue;
        }

        // If currently considered string is neither a keyword nor a valid variable, 
        // then that means input contains error
        else
        {
            std::cerr
                << "Error: invalid character " << input[pos]
                << " at position " << pos
                << "\nCurrent expression : " << input << '\n';
            exit(1);
        }
    }
}

void Parser::create_tree()
{
    tree_created = true;

    root = ParseTree(tokens).get_root();
}

void Parser::convert_to_cnf()
{
    converted_to_cnf = true;

    root = cnf(root);
}

std::set<std::string> Parser::get_symbols()
{
    if (!tokenized) tokenize();

    return symbols;
}

std::vector<Token> Parser::get_tokens()
{
    if (!tokenized) tokenize();

    return tokens;
}

Node* Parser::get_tree()
{
    if (!tokenized) tokenize();
    if (!tree_created) create_tree();

    return root;
}

Node* Parser::get_cnf_tree()
{
    if (!tokenized) tokenize();
    if (!tree_created) create_tree();
    if (!converted_to_cnf) convert_to_cnf();

    return root;
}

std::vector<std::set<std::string>> Parser::get_cnf_clauses()
{
    if (!tokenized) tokenize();
    if (!tree_created) create_tree();
    if (!converted_to_cnf) convert_to_cnf();

    return convert_root_node_to_clauses(root);
}

std::vector<HornClause> Parser::get_horn_clauses()
{
    if (!tokenized) tokenize();
    if (!tree_created) create_tree();

    return convert_root_node_to_horn_clauses(root);
}
