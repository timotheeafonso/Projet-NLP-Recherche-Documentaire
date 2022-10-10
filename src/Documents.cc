#include "Documents.hh"
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

            deleteSpecialChar(title);
            document.setTitle(tokenize(title));
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

        deleteSpecialChar(content);
        document.setContent(tokenize(content));
        // document.deleteStopwords(document._content);
        document.stem(document._content);

        _documents.push_back(document);

    }
}
