#pragma once
#include <vector>
#include "tokenizer.hpp"

class FormulaValidator
{
public:
    static bool validateFormula(const std::vector<Tokenizer::Token> &tokens);
};