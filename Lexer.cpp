#include <iostream>
#include "Lexer.h"
#include "KEYWORDS.h"

bool Lexer::skip_whitespace()
{
    while (fIndex < fInput.length() && isspace(fInput[fIndex]))
    {
        fIndex++;
    }
    if (fIndex < fInput.length())
        return true;
    return false;
}

bool Lexer::match(char c)
{
    skip_whitespace();
    if (fIndex < fInput.length() && fInput[fIndex] == c)
    {
        fIndex++;
        return true;
    }
    return false;
}

Lexer::Lexer(std::string input) :fInput(input), fIndex(0), fToken({})
{
    tokenize();
}

void Lexer::tokenize()
{
    fToken = {};
    while (fIndex < fInput.size())
    {
        if (!skip_whitespace()) break;

        size_t keyword_size = 0;

        for (const auto& keyword_token : KEYWORDS)
        {
            std::string keyword = keyword_token.second;

            if (fInput.substr(fIndex, keyword.size()) == keyword)
            {
                keyword_size = keyword.size();
                fToken.push_back(Token(keyword_token));
                break;
            }
        }

        if (keyword_size) 
        { 
            fIndex += keyword_size; 
            continue;
        }

        if (!skip_whitespace()) break;

        if (isalpha(fInput[fIndex]) || fInput[fIndex] == '_')
        {
            // Parse a variable
            size_t end = fIndex + 1;
            while (end < fInput.size() && (isalnum(fInput[end]) || fInput[end] == '_'))
            {
                end++;
            }
            std::string var = fInput.substr(fIndex, end - fIndex);

            fToken.push_back({ TokenType::VARIABLE, var });

            fIndex = end;
        }

        else
        {
            // If currently considered string is neither a keyword nor a valid variable, 
            // then that means input contains error
            std::cerr
                << "Error: invalid character " << fInput[fIndex]
                << " at fIndexition " << fIndex
                << "\nCurrent expression : " << fInput << '\n';
            exit(1);
        }
    }
}

