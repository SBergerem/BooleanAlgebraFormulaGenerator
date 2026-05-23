#include <string>
#include <vector>
#include "tokenizer.hpp"
#include "parser.hpp"

int main()
{
    std::string input = "(A OR (A AND (!B)))";
    std::vector<Tokenizer::Token> tokens = Tokenizer::tokenize(input);
    bool result = Parser::validateFormula(tokens);
    return 0;
}
