#include "SpellingCorrector.hh"
#include <cstring>
#include <iostream>
#include "Document.hh"
#include "Documents.hh"
#include "Query.hh"

Query::Query(std::string q){
    this->_content=q;
}

std::string Query::correctQuery() {
    std::string correctQuery;

    std::vector<std::string> stopwords = getStopword();
    
    SpellingCorrector corrector;
    corrector.load("../src/big.txt");
    std::string cleanQuery=deleteSpecialChar(this->_content);    
    std::vector<std::string> querryToken = tokenize(cleanQuery);
    
    for(std::string token : querryToken)
	{
		std::string correct(corrector.correct(token));
        correctQuery+=correct;
        correctQuery+=" ";

	}
    std::cout<<correctQuery;
    return correctQuery;
}