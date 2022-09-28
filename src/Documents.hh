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
};