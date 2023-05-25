#pragma once
#include <vector>
#include "TokenType.h"
#include "Token.h"
#include "KEYWORDS.h"

struct Node
{
    TokenType type;
    std::string value;
    std::vector<Node*> children;

//#define NODE_DEBUG
#ifdef NODE_DEBUG
    static size_t instance_created;
    static size_t instance_deleted;
#endif // NODE_DEBUG


    Node(TokenType type_, std::string value_, std::vector<Node*> children_ = std::vector<Node*>());

    Node(Token token_, std::vector<Node*> children_ = std::vector<Node*>());

    Node(TokenType type_, std::vector<Node*> children_ = std::vector<Node*>());

    ~Node();
};



