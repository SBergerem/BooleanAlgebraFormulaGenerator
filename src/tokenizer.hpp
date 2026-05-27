#pragma once

#include <vector>
#include <map>
#include <string>

class Tokenizer
{
public:
    // Tokens after Priority
    enum class TokenType
    {
        UNKNOWN,
        VARIABLE,
        OPEN_PARENTHESIS,
        CLOSE_PARENTHESIS,
        NOT,
        OR,
        NOR,
        XOR,
        AND,
        NAND
    };

    static const std::map<std::string, TokenType> OPERATORS;

    struct Token
    {
        TokenType type;
        std::string text;
    };

    static std::vector<Token> tokenize(const std::string &input);
    static bool isOneOf(TokenType value, std::initializer_list<TokenType> list);
    static int getPriorityOfOperation(TokenType tokenType);
};