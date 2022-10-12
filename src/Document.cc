#include "Document.hh"

std::string Document::toString() {
    return "\n" + _author;

    /*std::string text;

    for (auto word : _content)
        text += "\n" + word;

    return text;*/

    // return "\n\nDocument" + _number + "\n" + _title + "\n\n" + _author + "\n" + _editor + "\n" + _content;
}