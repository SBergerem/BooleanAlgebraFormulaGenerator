#pragma once

#include "tokenizer.hpp"

struct Node
{
    Tokenizer::Token token;

    Node(Tokenizer::Token token);
    virtual ~Node() = default;
};

struct Node_Invert : Node
{
    Node *child;

    Node_Invert(Tokenizer::Token token, Node *child);
    ~Node_Invert();
};

struct Node_Operator : Node
{
    Node *leftChild;
    Node *rightChild;

    Node_Operator(Tokenizer::Token token, Node *leftChild, Node *rightChild);
    ~Node_Operator();
};

struct Node_Variable : Node
{
    Node_Variable(Tokenizer::Token token);
};

class Parser
{
    private:
    static void parseExpression(const std::vector<Tokenizer::Token> &tokens)
public:
    static void parse(const std::vector<Tokenizer::Token> &tokens, Node *&rootNode);
};