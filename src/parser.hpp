#pragma once
#include <vector>
#include "tokenizer.hpp"

class Parser
{
public:
    static bool validateFormula(const std::vector<Tokenizer::Token> &tokens);
};