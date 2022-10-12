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
    std::map<std::string,double> tfIdf(Forest trees);
    std::vector<std::string> getTopX(Forest trees , int topX);
};
