#pragma once

#include "tokenizer.hpp"
#include "node.hpp"

class Parser
{
private:
    static bool checkForOuterParentheses(const std::vector<Tokenizer::Token> &tokens, size_t startIndex, size_t endIndex);
    static size_t getIndexOfOperatorByPrio(const std::vector<Tokenizer::Token> &tokens, size_t startIndex, size_t endIndex);
    static bool parseExpression(const std::vector<Tokenizer::Token> &tokens, size_t startIndex, size_t endIndex, Node *&Node);

public:
    static bool parse(const std::vector<Tokenizer::Token> &tokens, Node *&rootNode);
};