#include <iostream>
#include "Document.hh"
#include "Documents.hh"

int main() {
    Documents documents;
    documents.parse("../AP/AP891216");
    documents.print();

    return 0;
}
