#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
    GT,
    LT,
    PL,
    MI,
    DT,
    CM,
    LB,
    RB,
    UNK,
    EOF
};

struct Token 
{
    TokenType type;
    std::string text;
}

#endif // TOKEN_H
