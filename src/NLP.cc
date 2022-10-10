#include "NLP.hh"
#include <iostream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>
#include <bits/stdc++.h>
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include <utility>
#include <vector>
#include "../lib/porter/olestem/stemming/english_stem.h"
#include <cstdlib>

void NLP::deleteSpecialChar(std::string& text) {
    char specialChar[] = "_-.,();!?{}\"\"\\`$%€1234567890";
    int it = 0;

    for(char c : text){
        it++;
        if (isupper(c)){
            char lower = c + 32;
            std::replace(text.begin(), text.end(), c, lower);
        }
        for(char c2 : specialChar){
            if(c == c2){
                std::replace(text.begin(), text.end(), c, ' ');
            }
        }
    }
} 

std::vector<std::string> NLP::tokenize(std::string text) {
    std::vector<std::string> tokens;

    std::istringstream iss(text);
    std::string word;
    while (iss >> word) {
        tokens.push_back(word);
    }

    return tokens;
}


std::vector<std::string> NLP::getStopword(){
    std::vector<std::string> stopwords;
    std::ifstream file;
    file.open("../stopwords.txt", std::ios::in); // Opens a file to perform read operation using file object

    if (file.is_open()){ // Checking whether the file is open
        std::string tp;
        while (file >> tp) {
            stopwords.push_back(tp);
        }
    }

    file.close();
    return stopwords;
}

void NLP::deleteStopwords(std::vector<std::string>& tokens){
    std::vector<std::string> stopwords = getStopword();

    for(auto it = std::begin(tokens); it != std::end(tokens); ++it) {
        for(const auto& sw : stopwords) {
            if(*it == sw){
                tokens.erase(it);
                it--;
            }
        }
    }
}

void NLP::stem(std::vector<std::string>& tokens){
    std::wstring word;
    stemming::english_stem<> StemEnglish;
    std::vector<std::string> newList;

    for (const auto & it : tokens) {
        std::string token = it;
        auto* UnicodeTextBuffer = new wchar_t[it.length()+1];

        std::wmemset(UnicodeTextBuffer, 0, it.length()+1);
        std::mbstowcs(UnicodeTextBuffer, it.c_str(), it.length());
        word = UnicodeTextBuffer;
        StemEnglish(word);
        
        std::string str(word.length(), 0);
        std::transform(word.begin(), word.end(), str.begin(), [] (wchar_t c) {
            return (char)c;
        });

        newList.push_back(str);
    }
}