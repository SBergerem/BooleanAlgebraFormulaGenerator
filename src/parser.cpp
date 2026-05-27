#include <iostream>

#include "parser.hpp"

bool Parser::checkForOuterParentheses(const std::vector<Tokenizer::Token> &tokens, size_t startIndex, size_t endIndex)
{
    if (endIndex <= startIndex + 1)
        return false;

    if (tokens[startIndex].type != Tokenizer::TokenType::OPEN_PARENTHESIS)
        return false;

    if (tokens[endIndex].type != Tokenizer::TokenType::CLOSE_PARENTHESIS)
        return false;

    int parenthesisDepth = 0;
    for (size_t i = startIndex; i < endIndex; i++)
    {
        if (tokens[i].type == Tokenizer::TokenType::OPEN_PARENTHESIS) //
            parenthesisDepth++;

        if (tokens[i].type == Tokenizer::TokenType::CLOSE_PARENTHESIS) //
            parenthesisDepth--;

        if (parenthesisDepth == 0)
            return false;
    }

    return true;
}

size_t Parser::getIndexOfOperatorByPrio(const std::vector<Tokenizer::Token> &tokens, size_t startIndex, size_t endIndex)
{
    int parenthesisDepth = 0;
    int Priority = -1;
    size_t index = tokens.size();
    bool foundOperator = false;

    for (size_t i = endIndex + 1; i-- > startIndex;)
    {
        if (tokens[i].type == Tokenizer::TokenType::OPEN_PARENTHESIS)
            parenthesisDepth--;

        if (tokens[i].type == Tokenizer::TokenType::CLOSE_PARENTHESIS)
            parenthesisDepth++;

        if (parenthesisDepth == 0)
        {
            // Tokenizer::TokenType::XOR
            int currPriority = Tokenizer::getPriorityOfOperation(tokens[i].type);

            if (currPriority < 0)
                continue;

            if ((Priority > currPriority) || !foundOperator)
            {
                index = i;
                Priority = currPriority;
                foundOperator = true;
            }
        }
    }

    return index;
}

bool Parser::parseExpression(const std::vector<Tokenizer::Token> &tokens, size_t startIndex, size_t endIndex, Node *&resultNode)
{
    resultNode = nullptr;

    if (startIndex > endIndex)
        return false;

    if (startIndex == endIndex)
    {
        if (tokens[startIndex].type == Tokenizer::TokenType::VARIABLE)
        {
            resultNode = new Variable_Node(tokens[startIndex]);
            return true;
        }
        else
            return false;
    }

    if (checkForOuterParentheses(tokens, startIndex, endIndex))
    {
        startIndex++;
        endIndex--;
        return parseExpression(tokens, startIndex, endIndex, resultNode);
    }

    size_t operatorIndex = getIndexOfOperatorByPrio(tokens, startIndex, endIndex);
    if (operatorIndex < tokens.size())
    {
        Node *leftChildNode = nullptr;
        Node *rightChildNode = nullptr;

        if (!parseExpression(tokens, startIndex, operatorIndex - 1, leftChildNode))
            return false;

        if (!parseExpression(tokens, operatorIndex + 1, endIndex, rightChildNode))
        {
            delete leftChildNode;
            return false;
        }

        resultNode = new Operator_Node(tokens[operatorIndex], leftChildNode, rightChildNode);
        return true;
    }

    if (tokens[startIndex].type == Tokenizer::TokenType::NOT)
    {
        Node *childNode = nullptr;
        if (parseExpression(tokens, startIndex + 1, endIndex, childNode))
        {
            resultNode = new Invert_Node(tokens[startIndex], childNode);
            return true;
        }
    }

    return false;
}

bool Parser::parse(const std::vector<Tokenizer::Token> &tokens, Node *&rootNode)
{
    if (rootNode != nullptr)
    {
        delete rootNode;
        rootNode = nullptr;
    }

    if (tokens.size() == 0)
    {
        std::cout << "Tokencount is zero. Abort.." << std::endl;
        return false;
    }

    if (!parseExpression(tokens, 0, tokens.size() - 1, rootNode))
    {
        std::cout << "Could not parse expression. Abort.." << std::endl;
        return false;
    }

    return true;
}
