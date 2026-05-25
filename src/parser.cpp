#include <iostream>

#include "parser.hpp"

Node::Node(Tokenizer::Token token)
{
    this->token = token;
}

Node_Invert::Node_Invert(Tokenizer::Token token, Node *child)
    : Node(token)
{
    this->child = child;
}

Node_Invert::~Node_Invert()
{
    delete child;
}
Node_Operator::Node_Operator(Tokenizer::Token token, Node *leftChild, Node *rightChild)
    : Node(token)
{
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

Node_Operator::~Node_Operator()
{
    delete leftChild;
    delete rightChild;
}

Node_Variable::Node_Variable(Tokenizer::Token token)
    : Node(token) {}

bool Parser::parseExpression(const std::vector<Tokenizer::Token> &tokens, size_t startIndex, size_t endIndex, Node *&resultNode)
{
    resultNode = nullptr;

    if (startIndex == endIndex)
    {
        if (tokens[startIndex].type == Tokenizer::TokenType::VARIABLE)
        {
            resultNode = new Node_Variable(tokens[startIndex]);
            return true;
        }
        else
            return false;
    }

    if (tokens[startIndex].type == Tokenizer::TokenType::NOT)
    {
        Node *childNode = nullptr;
        if (parseExpression(tokens, startIndex + 1, endIndex, childNode))
        {
            resultNode = new Node_Invert(tokens[startIndex], childNode);
            return true;
        }
    }

        return false;
}

void Parser::parse(const std::vector<Tokenizer::Token> &tokens, Node *&rootNode)
{
    if (rootNode != nullptr)
    {
        delete rootNode;
        rootNode = nullptr;
    }

    if (tokens.size() == 0)
    {
        std::cout << "Tokencount is zero. Abort.." << std::endl;
        return;
    }

    if ((tokens.size() == 1) && (tokens[0].type == Tokenizer::TokenType::VARIABLE))
        rootNode = new Node_Variable(tokens[0]);

    if ((tokens.size() == 2) && (tokens[0].type == Tokenizer::TokenType::NOT))
    {
        Node *childNode = nullptr;
        if (tokens[1].type == Tokenizer::TokenType::VARIABLE)
            childNode = new Node_Variable(tokens[1]);
        rootNode = new Node_Invert(tokens[0], childNode);
    }

    if ((tokens.size() == 3) && Tokenizer::isOneOf(tokens[1].type,
                                                   {Tokenizer::TokenType::AND,
                                                    Tokenizer::TokenType::OR,
                                                    Tokenizer::TokenType::NAND,
                                                    Tokenizer::TokenType::NOR,
                                                    Tokenizer::TokenType::XOR}))
    {
        Node *leftChildNode = nullptr;
        Node *rightChildNode = nullptr;

        if (tokens[0].type == Tokenizer::TokenType::VARIABLE)
            leftChildNode = new Node_Variable(tokens[0]);

        if (tokens[2].type == Tokenizer::TokenType::VARIABLE)
            rightChildNode = new Node_Variable(tokens[2]);

        rootNode = new Node_Operator(tokens[1], leftChildNode, rightChildNode);
    }
}
