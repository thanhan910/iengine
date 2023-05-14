#include <string>
#include <vector>
#include "Token.h"

class Lexer
{
private:
    std::string fInput;
    size_t fIndex;
    
    bool skip_whitespace();
    bool match(char c);
    void tokenize();

public:
    Lexer(std::string input);
    std::vector<Token> fToken;
};