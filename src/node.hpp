#pragma once

#include "tokenizer.hpp"

enum class NodeType
{
    DEFAULT_NODE,
    VARIABLE_NODE,
    INVERT_NODE,
    OPERATOR_NODE
};

struct Node
{
    Tokenizer::Token token;
    NodeType nodeType;

    Node(Tokenizer::Token token, NodeType nodeType);
    virtual ~Node() = default;
};

struct Invert_Node : Node
{
    Node *child;

    Invert_Node(Tokenizer::Token token, Node *child);
    ~Invert_Node();
};

struct Operator_Node : Node
{
    Node *leftChild;
    Node *rightChild;

    Operator_Node(Tokenizer::Token token, Node *leftChild, Node *rightChild);
    ~Operator_Node();
};

struct Variable_Node : Node
{
    Variable_Node(Tokenizer::Token token);
};