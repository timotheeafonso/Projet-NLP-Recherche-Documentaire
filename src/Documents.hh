#pragma once
#include "Document.hh"
#include <vector>

class Documents {
private:
    std::vector<Document> _documents;

public:
    Documents()=default;;
    void print();

    void parse(const std::string& path);
    std::string deleteSpecialChar(std::string text);
    std::vector<std::string> tokenize(std::string str);
    std::vector<std::string> getStopword();
    std::vector<std::string> deleteStopwords(std::vector<std::string> tokens, std::vector<std::string> stopwords);
    std::vector<std::string> stem(std::vector<std::string> tokens);
};