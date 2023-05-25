#include "Node.h"
#include <iostream>

#ifdef NODE_DEBUG
size_t Node::instance_created = 0;
size_t Node::instance_deleted = 0;

#endif // NODE_DEBUG


Node::Node(TokenType type_, std::string value_, std::vector<Node*> children_) :
    type(type_), value(value_), children(children_)
{
#ifdef NODE_DEBUG
    ++instance_created;
#endif
}

Node::Node(Token token_, std::vector<Node*> children_) :
    type(token_.type), value(token_.value), children(children_)
{
#ifdef NODE_DEBUG
    ++instance_created;
#endif
}

Node::Node(TokenType type_, std::vector<Node*> children_) :
    type(type_), children(children_)
{
#ifdef NODE_DEBUG
    ++instance_created;
#endif

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
#ifdef NODE_DEBUG
    ++instance_deleted;
#endif
    /*for (Node* child : children)
    {
        delete child;
    }*/
}


