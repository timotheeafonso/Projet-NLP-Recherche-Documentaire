
#pragma once
#include <string>
#include <vector>

class NLP {
private:

public:
    NLP() = default;;
    std::string deleteSpecialChar(std::string text);
    std::vector<std::string> tokenize(std::string str);
    std::vector<std::string> getStopword();
    std::vector<std::string> deleteStopwords(std::vector<std::string> tokens, std::vector<std::string> stopwords);
    std::vector<std::string> stem(std::vector<std::string> tokens);
};