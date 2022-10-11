#pragma once
#include <string>
#include <vector>
#include "NLP.hh"
#include "Forest.hh"
#include <map>

class Query : public NLP{
private:
    std::string _content;

public:
    Query(std::string q);
    std::string correctQuery();
    std::map<std::string, std::vector<double>> tfIdf(Forest trees);
};
