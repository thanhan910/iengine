#include "Node.h"
#include <iostream>

size_t Node::instance_created = 0;
size_t Node::instance_deleted = 0;

Node::Node(TokenType type_, std::string value_, std::vector<Node*> children_) :
    type(type_), value(value_), children(children_)
{
    ++instance_created;
}

Node::Node(Token token_, std::vector<Node*> children_) :
    type(token_.type), value(token_.value), children(children_)
{
    ++instance_created;
}

Node::Node(TokenType type_, std::vector<Node*> children_) :
    type(type_), children(children_)
{
    ++instance_created;

    auto it = KEYWORDS.find(type_);

    if (it != KEYWORDS.end())
    {
        value = KEYWORDS[type_];
    }

    else
    {
        value = "";
    }
}

Node::~Node()
{
    ++instance_deleted;
    /*for (Node* child : children)
    {
        delete child;
    }*/
}


