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
    std::string _originalContent;
    std::string _originalTitle;


public:
    Document() = default;;
    std::string toString();


    std::string getNumber() { return _number; }
    std::vector<std::string> getTitle() { return _title; }
    std::string getOriginalTitle() { return _originalTitle; }
    std::vector<std::string> getContent() { return _content; }
    std::string getOriginalContent() { return _originalContent; }
    std::string getAuthor() { return _author; }
    std::string getEditor() { return _editor; }


    void setNumber(const std::string &number) { _number = number; };
    void setTitle(const std::vector<std::string> &title) { _title = title; };
    void setOriginalTitle(const std::string &originalTitle) { _originalTitle = originalTitle; };
    void setAuthor(const std::string &author) { _author = author; };
    void setEditor(const std::string &editor) { _editor = editor; };
    void setContent(const std::vector<std::string> &content) { _content = content; }
    void setOriginalContent(const std::string &originalContent) { _originalContent = originalContent; }

};