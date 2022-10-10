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

    SpellingCorrector corrector;
    corrector.load("../src/big.txt");
    deleteSpecialChar(this->_content);
    std::vector<std::string> querryToken = tokenize(this->_content);
    
    for(std::string token : querryToken)
	{
		std::string correct(corrector.correct(token));
        correctQuery += correct;
        correctQuery += " ";

	}
    correctQuery.pop_back();
    std::cout << correctQuery;
    return correctQuery;
}