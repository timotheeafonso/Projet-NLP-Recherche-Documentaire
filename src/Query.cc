#include "SpellingCorrector.hh"
#include <cstring>
#include <iostream>
#include "Document.hh"
#include "Documents.hh"
#include "Query.hh"

#include "Query.hh"
#include <map>
#include "Word.hh"
#include <math.h>    
#include <iterator>  
#include <vector>

#include <algorithm>

bool cmp(std::pair<std::string, double>& a,
         std::pair<std::string, double>& b)
{
    return a.second > b.second;
}


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
    return correctQuery;
}

std::map<std::string, double> Query::tfIdf(Forest trees){

    std::vector<std::string> stopwords = getStopword();
    deleteSpecialChar(this->_content);   
    
    std::vector<std::string> querryToken = tokenize(this->_content);
    deleteStopwords(querryToken);
    std::cout<<querryToken.size()<<std::endl;
    stem(querryToken); 
    std::map<std::string, std::vector<double>> tfidf;
    std::map<std::string,double> scores;
    std::vector<int> df;
    std::vector<double> idf;
    int N=trees.getForest().size();
    std::cout<<"\n";

    for (int i = 0; i < querryToken.size(); i++) { //init df, idf à 0
        df.push_back(0);
        idf.push_back(0.);
    }
    for(auto tree: trees.getForest()) {
        std::vector<double> tf;
        
        for(int i = 0; i < querryToken.size(); i++)
        {
            if (querryToken[i].back() == (char) 42) {
                std::string subToken = querryToken[i].substr(0, querryToken[i].size()-1);
                if(tree.jokerSearch(subToken) != 0) {
                    df[i] += 1;
                    int occ= tree.jokerSearch(subToken);
                    tf.push_back(1 + log10(occ));       // Occurence du token i dans le document courant
                }
                else {
                    tf.push_back(0);       // Occurence du token i dans le document courant
                }
            }
            else {
                if(tree.search(querryToken[i]) != 0){
                    df[i] += 1;
                    int occ= tree.search(querryToken[i]);
                    tf.push_back(1 + log10(occ));       // Occurence du token i dans le document courant
                }
                else {
                    tf.push_back(0);       // Occurence du token i dans le document courant
                }
            }
        }
        tfidf.insert(std::pair<std::string, std::vector<double>>(tree.getNumber(), tf)); 
    }
    std::cout<<"\n\n";
    for(int i = 0; i < querryToken.size(); i++){
        if(df[i]!=0){
            idf[i]=log10(N/df[i]); // Occurence du token i dans les documents
            std::cout<<querryToken[i]<<" : "<<idf[i]<<"\n";
        }
    }
    
    for (std::pair<std::string, std::vector<double>> element : tfidf) {
        std::vector<double> newVect;
        double s=0;
        for(int j = 0; j < querryToken.size(); j++){
            s+=element.second[j]*idf[j];
            newVect.push_back(element.second[j]*idf[j]);
        }
        s=s/querryToken.size();
        tfidf[element.first] = newVect;
        scores.insert(std::pair<std::string, double>(element.first, s)); 

    }

    for (auto it: tfidf) {
        std::cout<<it.first<<" : ";
        for(int i = 0; i < it.second.size(); i++){
            std::cout<<querryToken[i]<<"("<<it.second[i]<<"), ";
        }
        std::cout<<"\n";
    }



    return scores;

}


std::vector<std::string> Query::getTopX(Forest trees,int topX){
    std::vector<std::string> listTop;
    std::map<std::string, double> scores=this->tfIdf(trees);

    std::vector<std::pair<std::string, double> > A;
    for (auto& it : scores) {
        A.push_back(it);
    }
  
    sort(A.begin(), A.end(), cmp);
    
    int t=0;
    for (auto& it : A) {
        if(t<topX){
            listTop.push_back(it.first);
        }
        t++;
    }
    return listTop;

}

