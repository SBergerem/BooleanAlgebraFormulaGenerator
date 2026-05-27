#include "normalizer.hpp"

void Normalizer::replaceAll(std::string &inputString, const std::string &textToReplace, const std::string &replaceText)
{
    size_t textPos = inputString.find(textToReplace);
    while (textPos != std::string::npos)
    {
        inputString.replace(textPos, textToReplace.size(), replaceText);
        textPos = inputString.find(textToReplace, textPos + replaceText.size());
    }
}

void Normalizer::normalizeInputString(std::string &inputString)
{
    replaceAll(inputString, "⊕", " XOR ");
    replaceAll(inputString, "¬", " NOT ");
    replaceAll(inputString, "∧", " AND ");
    replaceAll(inputString, "∨", " OR ");
    replaceAll(inputString, "!", " NOT ");
    replaceAll(inputString, "(", " ( ");
    replaceAll(inputString, ")", " ) ");
}