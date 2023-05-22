#include "AST.h"
#include <iostream>


bool AST::parser_is_in_scope()
{
    return index < tokens.size();
}

void AST::move_parser_to_next_token()
{
    ++index;
}

bool AST::current_token_is(TokenType type)
{
    return parser_is_in_scope() && tokens[index].type == type;
}

AST::AST(std::vector<Token> tokens_) :
    tokens(tokens_),
    index(0)
{
    root_node = new Node(AND, "AND");

    while (parser_is_in_scope())
    {
        Node* expr = parse_expression();

        if (expr == nullptr)
        {
            std::cerr << "Unexpected token: " << tokens[index].value << std::endl;
            exit(1);
        }

        root_node->children.push_back(expr);

        if (current_token_is(SEMICOLON))
        {
            move_parser_to_next_token();

            if (!parser_is_in_scope())
            {
                break;
            }
        }

        else if (root_node->children.size() <= 1)
        {
            root_node = expr;
        }
    }
}

Node* AST::get_root()
{
    return root_node;
}

Node* AST::parse_expression()
{
    return parse_biconditional();
}

Node* AST::parse_biconditional()
{
    Node* left = parse_implication();

    std::vector<Node*> nodes = { left };

    while (current_token_is(BICONDITIONAL))
    {
        move_parser_to_next_token();

        Node* right = parse_implication();

        if (right == nullptr)
        {
            std::cerr << "Expected right-hand side of biconditional" << std::endl;
            exit(1);
        }

        nodes.push_back(right);
    }
    if (nodes.size() > 1)
    {
        return new Node{ BICONDITIONAL, "BICONDITIONAL", nodes };
    }
    else
    {
        return left;
    }
}

Node* AST::parse_implication()
{
    Node* left = parse_disjunction();

    std::vector<Node*> nodes = { left };

    while (current_token_is(IMPLIES))
    {
        move_parser_to_next_token();

        Node* right = parse_disjunction();

        if (right == nullptr)
        {
            std::cerr << "Expected right-hand side of implication" << std::endl;
            exit(1);
        }

        nodes.push_back(right);
    }

    if (nodes.size() > 1)
    {
        return new Node{ IMPLIES, "IMPLIES", nodes };
    }

    else
    {
        return left;
    }
}

Node* AST::parse_disjunction()
{
    Node* left = parse_conjunction();

    std::vector<Node*> nodes = { left };

    while (current_token_is(OR))
    {
        move_parser_to_next_token();

        Node* right = parse_conjunction();

        if (right == nullptr)
        {
            std::cerr << "Expected right-hand side of disjunction" << std::endl;
            exit(1);
        }
        nodes.push_back(right);
    }
    if (nodes.size() > 1)
    {
        return new Node{ OR, "OR", nodes };
    }
    else
    {
        return left;
    }
}

Node* AST::parse_conjunction()
{
    Node* left = parse_negation();

    std::vector<Node*> nodes = { left };

    while (current_token_is(AND))
    {
        move_parser_to_next_token();

        Node* right = parse_negation();

        if (right == nullptr)
        {
            std::cerr << "Expected right-hand side of conjunction" << std::endl;
            exit(1);
        }

        nodes.push_back(right);
    }

    if (nodes.size() > 1)
    {
        return new Node{ AND, "AND", nodes };
    }

    else
    {
        return left;
    }
}

Node* AST::parse_negation()
{
    if (current_token_is(NOT))
    {
        Node* node = new Node{ tokens[index] };

        move_parser_to_next_token();

        Node* child = parse_parentheses_or_symbol();

        if (child == nullptr)
        {
            std::cerr << "Expected expression after negation" << std::endl;
            exit(1);
        }

        node->children.push_back(child);

        return node;
    }

    else
    {
        return parse_parentheses_or_symbol();
    }
}

Node* AST::parse_parentheses_or_symbol()
{
    if (current_token_is(LPAREN))
    {
        move_parser_to_next_token();

        Node* node = parse_expression();

        if (current_token_is(RPAREN))
        {
            move_parser_to_next_token();

            return node;
        }
        else
        {
            std::cerr << "Expected closing parenthesis" << std::endl;
            exit(1);
        }
    }

    else if (current_token_is(SYMBOL))
    {
        Node* node = new Node{ tokens[index] };

        move_parser_to_next_token();

        return node;
    }

    else
    {
        return nullptr;
    }
}


