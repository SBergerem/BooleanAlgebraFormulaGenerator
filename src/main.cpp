#include <string>
#include <vector>
#include "tokenizer.hpp"
#include "formula_validator.hpp"

int main()
{
    std::string input = "(A OR (A AND (!B)))";
    std::vector<Tokenizer::Token> tokens = Tokenizer::tokenize(input);
    bool result = FormulaValidator::validateFormula(tokens);
    return 0;
}
