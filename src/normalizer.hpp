#pragma once

#include <string>

class Normalizer
{
private:
    static void replaceAll(std::string &inputString, const std::string &textToReplace, const std::string &replaceText);

public:
    static void normalizeInputString(std::string &inputString);
};