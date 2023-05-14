#pragma once

#include "TokenType.h"
#include "Node.h"

#include <string>
#include <vector>
#include <iostream>

class ParseTree
{
public:

    Node* root_node;

    ParseTree(std::vector<Token> tokens_);

    // Define functions to parse the grammar rules
    void parse();

private:

    size_t index;
    std::vector<Token> tokens;


    // Helper functions, just for readability
    bool parser_is_in_scope();
    void move_parser_to_next_token();
    bool current_token_is(TokenType type);

    // Define recursive descent functions to parse the grammar rules 
    Node* parse_expression();
    Node* parse_implication();
    Node* parse_biconditional();
    Node* parse_disjunction();
    Node* parse_conjunction();
    Node* parse_negation();
    Node* parse_atom();

};




