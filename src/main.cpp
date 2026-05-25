#include <string>
#include <vector>
#include "tokenizer.hpp"
#include "validator.hpp"
#include "parser.hpp"

int main()
{
    std::string input = "A OR B";
    std::vector<Tokenizer::Token> tokens = Tokenizer::tokenize(input);
    if (Validator::validateFormula(tokens))
    {
        Node *rootNode = nullptr;
        Parser::parse(tokens, rootNode);
        delete rootNode;
    }
    return 0;
}
