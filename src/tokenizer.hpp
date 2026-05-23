#pragma once

#include <vector>
#include <map>
#include <string>

class Tokenizer
{
public:
    enum class TokenType
    {
        VARIABLE,
        OPEN_PARENTHESIS,
        CLOSE_PARENTHESIS,
        NOT,
        AND,
        OR,
        NAND,
        NOR,
        XOR,
        UNKNOWN
    };

    static const std::map<std::string, TokenType> OPERATORS;

    struct Token
    {
        TokenType type;
        std::string text;
    };

    static std::vector<Token> tokenize(const std::string &input);
    static bool isOneOf(TokenType value, std::initializer_list<TokenType> list);
};