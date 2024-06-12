#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include "Token.h"

class Lexer
{
public:
    Lexer(const std::string& source) : source(source), position(0) {}
    std::vector<Token> tokenize();
private:
    Token nextToken();
    char currentChar() const;
    void advance();

    std::string source;
    size_t position
};

#endif // LEXER_H
