#pragma once
#include "NLP.hh"
#include <string>
#include <vector>

class Document : public NLP {
friend class Documents;

private:
    std::string _number;
    std::vector<std::string> _title;
    std::string _author;
    std::string _editor;
    std::vector<std::string> _content;

public:
    Document() = default;;
    std::string toString();


    std::string getNumber() { return _number; }
    std::vector<std::string> getTitle() { return _title; }
    std::vector<std::string> getContent() { return _content; }

    void setNumber(const std::string &number) { _number = number; };
    void setTitle(const std::vector<std::string> &title) { _title = title; };
    void setAuthor(const std::string &author) { _author = author; };
    void setEditor(const std::string &editor) { _editor = editor; };
    void setContent(const std::vector<std::string> &content) { _content = content; }
};