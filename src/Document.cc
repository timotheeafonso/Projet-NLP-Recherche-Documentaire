#include "Document.hh"

std::string Document::toString() {
    return "\n\nDocument" + _number + "\n" + _title + "\n" + _author + "\n" + _editor + "\n" + _content;
}
