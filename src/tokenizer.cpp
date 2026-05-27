#include <cctype>
#include <algorithm>
#include <initializer_list>
#include "tokenizer.hpp"

const std::map<std::string, Tokenizer::TokenType> Tokenizer::OPERATORS = {
    {"(", TokenType::OPEN_PARENTHESIS},
    {")", TokenType::CLOSE_PARENTHESIS},
    {"NOT", TokenType::NOT},
    {"!", TokenType::NOT},
    {"¬", TokenType::NOT},
    {"AND", TokenType::AND},
    {"∧", TokenType::AND},
    {"OR", TokenType::OR},
    {"∨", TokenType::OR},
    {"NAND", TokenType::NAND},
    {"NOR", TokenType::NOR},
    {"XOR", TokenType::XOR},
    {"⊕", TokenType::XOR}};

bool Tokenizer::isOneOf(TokenType value, std::initializer_list<TokenType> list)
{
    return std::find(list.begin(), list.end(), value) != list.end();
}

int Tokenizer::getPriorityOfOperation(TokenType tokenType)
{
    if (isOneOf(tokenType, {TokenType::OR,
                            TokenType::NOR}))
        return 0;

    if (tokenType == TokenType::XOR)
        return 1;

    if (isOneOf(tokenType, {TokenType::AND,
                            TokenType::NAND}))
        return 2;

    return -1;
}

std::vector<Tokenizer::Token> Tokenizer::tokenize(const std::string &input)
{
    std::vector<Tokenizer::Token> tokens;

    for (std::size_t i = 0; i < input.size(); i++)
    {
        if (input[i] == ' ')
            continue;

        if (isalnum(input[i]))
        {
            for (std::size_t j = i; j < input.size(); j++)
            {
                bool isLastChar = (j == input.size() - 1);
                bool isDelimiterChar = ((input[j] == '(') || (input[j] == ')') || (input[j] == ' ') //
                                        || (input[j] == '!') || (input[j] == '¬'));

                if (isLastChar || isDelimiterChar)
                {
                    std::string substring;

                    if (isDelimiterChar)
                        substring = input.substr(i, j - i);
                    else
                        substring = input.substr(i, j - i + 1);

                    if (Tokenizer::OPERATORS.contains(substring))
                    {
                        tokens.push_back(Tokenizer::Token{OPERATORS.at(substring), substring});
                    }
                    else
                    {
                        tokens.push_back(Tokenizer::Token{Tokenizer::TokenType::VARIABLE, substring});
                    }

                    i = j;
                    if (isDelimiterChar)
                        i--;

                    break;
                }
                else
                    continue;
            }
        }
        else
        {
            if (OPERATORS.contains(std::string(1, input[i])))
                tokens.push_back(Tokenizer::Token{OPERATORS.at(std::string(1, input[i])), std::string(1, input[i])});
            else
                tokens.push_back(Tokenizer::Token{Tokenizer::TokenType::UNKNOWN, std::string(1, input[i])});
        }
    }

    return tokens;
}