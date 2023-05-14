#include "KEYWORDS.h"

std::map<TokenType, std::string> KEYWORDS = {
    {TokenType::LPAREN, "("},
    {TokenType::RPAREN, ")"},
    {TokenType::BICONDITIONAL, "<=>"},
    {TokenType::IMPLIES, "=>"},
    {TokenType::AND, "&"},
    {TokenType::OR, "||"},
    {TokenType::NOT, "~"},
    {TokenType::SEMICOLON, ";"}
};