#pragma once
#include "Document.hh"
#include <vector>

class Documents {
private:
    std::vector<Document> _documents;

public:
    Documents()=default;;
    void print();

    std::vector<Document> getDocuments() { return _documents; }

    void parse(const std::string& path);
    std::string deleteSpecialChar(std::string text);
    std::vector<std::string> tokenize(const std::string& str);
};