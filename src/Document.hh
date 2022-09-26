#pragma once
#include <string>

class Document {
protected:
    std::string ID;
    std::string title;
    std::string author;
    std::string editor;

public:
    static void parse(const std::string& path);
};