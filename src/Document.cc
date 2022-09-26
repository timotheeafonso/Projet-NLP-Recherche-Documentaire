#include "Document.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "../lib/rapidxml-1.13/rapidxml.hpp"

void Document::parse(const std::string& path) {
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
        // Get the document number
        rapidxml::xml_node<> * docNumberNode = docNode->first_node("DOCNO");
        std::cout << "\n\n\tDocument" << docNumberNode->value();
        std::cout << std::endl;

        // Gets the title and subtitles of the document
        std::string title;

        for (rapidxml::xml_node<> * titleNode = docNode->first_node("HEAD"); titleNode; titleNode = titleNode->next_sibling()) {
            title += "\n";
            title += titleNode->value();
        }

        std::cout << title;

        // Gets the author of the document
        rapidxml::xml_node<> * authorNode = docNode->first_node("BYLINE");
        if (authorNode) {
            std::cout << authorNode->value();
            std::cout << std::endl;

            // Gets the editor pof the document
            rapidxml::xml_node<> * editorNode = authorNode->next_sibling();

            if (strcmp(editorNode->name(), "BYLINE") == 0) {
                std::cout << editorNode->value();
                std::cout << std::endl;
            }
        }

        // Gets the content of the document (notes included)
        std::string text;

        for (rapidxml::xml_node<> * textNode = docNode->first_node("TEXT"); textNode; textNode = textNode->next_sibling()) {
            text += textNode->value();
        }

        std::cout << text;
    }
}
