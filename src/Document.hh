#pragma once
#include <string>

class Document {
private:
    std::string _number;
    std::string _title;
    std::string _author;
    std::string _editor;
    std::string _content;

public:
    Document() = default;;
    std::string toString();

    void setNumber(const std::string &number) { _number = number; };
    void setTitle(const std::string &title) { _title = title; };
    void setAuthor(const std::string &author) { _author = author; };
    void setEditor(const std::string &editor) { _editor = editor; };
    void setContent(const std::string &content) { _content = content; }
};