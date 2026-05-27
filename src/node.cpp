#include "node.hpp"

Node::Node(Tokenizer::Token token, NodeType nodeType)
{
    this->token = token;
    this->nodeType = nodeType;
}

Invert_Node::Invert_Node(Tokenizer::Token token, Node *child)
    : Node(token, NodeType::INVERT_NODE)
{
    this->child = child;
}

Invert_Node::~Invert_Node()
{
    delete child;
}
Operator_Node::Operator_Node(Tokenizer::Token token, Node *leftChild, Node *rightChild)
    : Node(token, NodeType::OPERATOR_NODE)
{
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

Operator_Node::~Operator_Node()
{
    delete leftChild;
    delete rightChild;
}

Variable_Node::Variable_Node(Tokenizer::Token token)
    : Node(token, NodeType::VARIABLE_NODE) {}