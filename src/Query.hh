#pragma once
#include <string>
#include <vector>
#include "NLP.hh"

class Query : public NLP{
private:
    std::string _content;

public:
    Query(std::string q);
    std::string correctQuery();

};