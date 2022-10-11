
#pragma once
#include <string>
#include <vector>

class NLP {
private:

public:
    NLP() = default;;
    std::vector<std::string> getStopword();
    void deleteSpecialChar(std::string& text);
    std::vector<std::string> tokenize(std::string str);
    void deleteStopwords(std::vector<std::string>& tokens);
    void stem(std::vector<std::string>& tokens);
};