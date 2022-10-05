#pragma once
#include "Document.hh"
#include "NLP.hh"
#include <vector>

class Documents : public NLP {
private:
    std::vector<Document> _documents;

public:
    Documents()=default;;
    void print();
    std::vector<Document> getDocuments();
    void parse(const std::string& path);

};