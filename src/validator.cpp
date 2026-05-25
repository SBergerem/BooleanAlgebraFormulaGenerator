#include "validator.hpp"

bool Validator::validateFormula(const std::vector<Tokenizer::Token> &tokens)
{
    if (tokens.size() == 0)
        return false;

    if (Tokenizer::isOneOf(tokens[0].type,
                           {Tokenizer::TokenType::AND,
                            Tokenizer::TokenType::OR,
                            Tokenizer::TokenType::NAND,
                            Tokenizer::TokenType::NOR,
                            Tokenizer::TokenType::XOR,
                            Tokenizer::TokenType::CLOSE_PARENTHESIS,
                            Tokenizer::TokenType::UNKNOWN}))
        return false;

    if (Tokenizer::isOneOf(tokens[tokens.size() - 1].type,
                           {Tokenizer::TokenType::NOT,
                            Tokenizer::TokenType::AND,
                            Tokenizer::TokenType::OR,
                            Tokenizer::TokenType::NAND,
                            Tokenizer::TokenType::NOR,
                            Tokenizer::TokenType::XOR,
                            Tokenizer::TokenType::OPEN_PARENTHESIS,
                            Tokenizer::TokenType::UNKNOWN}))
        return false;

    int parenthesisDepth = 0;

    for (size_t i = 0; i < tokens.size(); i++)
    {
        Tokenizer::Token token = tokens[i];

        if (token.type == Tokenizer::TokenType::UNKNOWN)
            return false;

        if (token.type == Tokenizer::TokenType::OPEN_PARENTHESIS)
            parenthesisDepth++;

        if (token.type == Tokenizer::TokenType::CLOSE_PARENTHESIS)
        {
            parenthesisDepth--;
            if (parenthesisDepth < 0)
                return false;
        }

        if ((i == 0) || ((i > 0) && Tokenizer::isOneOf(tokens[i - 1].type,
                                                       {Tokenizer::TokenType::OPEN_PARENTHESIS,
                                                        Tokenizer::TokenType::NOT,
                                                        Tokenizer::TokenType::AND,
                                                        Tokenizer::TokenType::OR,
                                                        Tokenizer::TokenType::NAND,
                                                        Tokenizer::TokenType::NOR,
                                                        Tokenizer::TokenType::XOR})))
        {
            if ((i == 0) && Tokenizer::isOneOf(token.type,
                                               {Tokenizer::TokenType::CLOSE_PARENTHESIS,
                                                Tokenizer::TokenType::AND,
                                                Tokenizer::TokenType::OR,
                                                Tokenizer::TokenType::NAND,
                                                Tokenizer::TokenType::NOR,
                                                Tokenizer::TokenType::XOR}))
                return false;

            if ((i > 0) && Tokenizer::isOneOf(token.type,
                                              {Tokenizer::TokenType::CLOSE_PARENTHESIS,
                                               Tokenizer::TokenType::AND,
                                               Tokenizer::TokenType::OR,
                                               Tokenizer::TokenType::NAND,
                                               Tokenizer::TokenType::NOR,
                                               Tokenizer::TokenType::XOR}))
                return false;
        }
        else // Case: Before was VARIABLE, CLOSE_PARENTHESIS
        {
            if (Tokenizer::isOneOf(token.type,
                                   {Tokenizer::TokenType::VARIABLE,
                                    Tokenizer::TokenType::NOT,
                                    Tokenizer::TokenType::OPEN_PARENTHESIS}))
                return false;
        }
    }

    if (parenthesisDepth != 0)
        return false;

    return true;
}