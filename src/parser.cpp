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

    /*    for (Tokenizer::Token token : tokens)
        {
            if (token.type == Tokenizer::TokenType::VARIABLE)
                if (rootNode == nullptr)
                    rootNode = new Node(token);
        } */
}
