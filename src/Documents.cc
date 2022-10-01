#include "Documents.hh"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>
#include <bits/stdc++.h>
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include <vector>

void Documents::print() {
    for (auto doc : _documents) {
        std::cout << doc.toString();
    }
}

void Documents::parse(const std::string& path) {    
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> * rootNode = nullptr;

    // Reads the file at the given path
    std::ifstream file(path);
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parses the buffer
    doc.parse<0>(&buffer[0]);

    // Finds out the root node DOCS
    rootNode = doc.first_node("DOCS");
    
    // Loops over each documents    
    for (rapidxml::xml_node<> * docNode = rootNode->first_node("DOC"); docNode; docNode = docNode->next_sibling()) {
        
        Document document;
        
        // Sets the document number
        document.setNumber(docNode->first_node("DOCNO")->value());
        
        // Gets the title and subtitles and assign it to the document if they exist
        if (docNode->first_node("HEAD")) {
            std::string title;
            for (rapidxml::xml_node<> *titleNode = docNode->first_node("HEAD");
                 strcmp(titleNode->name(), "HEAD") == 0; titleNode = titleNode->next_sibling()) {
                title += "\n";
                title += titleNode->value();
            }
            document.setTitle(Documents::tokenize(Documents::deleteSpecialChar(title)));
        }

        // Gets the author of the document
        rapidxml::xml_node<> * authorNode = docNode->first_node("BYLINE");
        if (authorNode) {
            std::string author = authorNode->value();
            document.setAuthor(author.substr(3));

            // Gets the editor of the document
            rapidxml::xml_node<> * editorNode = authorNode->next_sibling();
            if (strcmp(editorNode->name(), "BYLINE") == 0) {
                document.setEditor(editorNode->value());
            }
        }

        // Gets the content of the document (notes included)
        std::string content;
        for (rapidxml::xml_node<> * contentNode = docNode->first_node("TEXT"); contentNode; contentNode = contentNode->next_sibling()) {
            content += contentNode->value();
        }
        document.setContent(Documents::tokenize(Documents::deleteSpecialChar(content)));

        _documents.push_back(document);
        
    }
    
    
}

std::string Documents::deleteSpecialChar(std::string text) {

    char specialChar[]=".,();!?{}\"\"$%€1234567890";
    std::string s=text;
    int it=0;
    for(char c : s){
        it++;
        if (isupper(c)){
            char lower = c + 32;
            std::replace( s.begin(), s.end(), c,lower);
        }
        for(char c2 : specialChar){
            if(c==c2){
                std::replace( s.begin(), s.end(), c,' ');
            }
        }
    }

    return s;
} 


std::vector<std::string> Documents::tokenize(std::string text) {

    char delim =' ';
    std::vector<std::string> tokens;
    std::string temp = "";
    int space=0;
    for(int i = 0; i < text.length(); i++){
        if(text[i] == delim){
            if(space==0)
                tokens.push_back(temp);
            temp = "";
            space++;
            
        }
        else{
            space=0;
            if(text[i]!=' ')
                temp += text[i];    
        }       
    }
    tokens.push_back(temp);
    return tokens;
}


std::vector<std::string> Documents::getStopword(){
    std::vector<std::string> stopwords;
    std::ifstream newfile;
    newfile.open("../stopwords.txt",std::ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){ //checking whether the file is open
        std::string tp;
        while (newfile >> tp) {
            
            stopwords.push_back(tp);
        }
    }
    newfile.close();
    return stopwords;
}

std::vector<std::string> Documents::deleteStopwords(std::vector<std::string> tokens, std::vector<std::string> stopwords){

    for(std::vector<std::string>::iterator it = std::begin(tokens); it != std::end(tokens); ++it){
        for(std::vector<std::string>::iterator it2 = std::begin(stopwords); it2 != std::end(stopwords); ++it2){
            if(*it==*it2){
                tokens.erase(it);
                it--;
                
            }
        }
    }
    return tokens;
}
