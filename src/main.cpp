#include <string>
#include <vector>
#include "tokenizer.hpp"
#include "validator.hpp"
#include "parser.hpp"
#include "normalizer.hpp"

int main()
{
    std::string input = "(A AND B) OR (!A AND !B)";
    Normalizer::normalizeInputString(input);
    std::vector<Tokenizer::Token> tokens = Tokenizer::tokenize(input);
    if (Validator::validateFormula(tokens))
    {
        Node *rootNode = nullptr;
        Parser::parse(tokens, rootNode);
        delete rootNode;
    }
    return 0;
}
