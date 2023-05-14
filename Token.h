#pragma once
#include "TokenType.h"
#include <string>

struct Token
{
    TokenType type;
    std::string value;

    Token(TokenType type_, std::string value_) :
        type(type_), value(value_)
    {
    }
    Token(const std::pair<TokenType, std::string> p) :
        type(p.first), value(p.second)
    {
    }
};

