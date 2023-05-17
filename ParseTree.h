#pragma once

#include "TokenType.h"
#include "Node.h"
#include <string>
#include <vector>

class ParseTree
{
public:

    // Constructor will immediately parse the tokens
    ParseTree(std::vector<Token> tokens_);

    Node* get_root();

private:

    // Root node of the tree
    Node* root_node;

    size_t index;
    std::vector<Token> tokens;

    // Helper functions, just for readability
    bool parser_is_in_scope();
    void move_parser_to_next_token();
    bool current_token_is(TokenType type);

    // Define recursive descent functions to parse the tokens 
    Node* parse_expression();
    Node* parse_implication();
    Node* parse_biconditional();
    Node* parse_disjunction();
    Node* parse_conjunction();
    Node* parse_negation();
    Node* parse_atom();
};




