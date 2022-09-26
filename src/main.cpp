#include <iostream>
#include "Document.hh"

int main() {
    Document doc = *new Document();
    doc.parse("../AP/AP891216");;


    return 0;
}
