#pragma once
#include <vector>
#include "tokenizer.hpp"

class Validator
{
public:
    static bool validateFormula(const std::vector<Tokenizer::Token> &tokens);
};