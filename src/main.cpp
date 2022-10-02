#include <iostream>
#include "Document.hh"
#include "Documents.hh"
#include "BTree.hh"
#include "Word.hh"

int main() {
    Documents documents;
    documents.parse("../AP/AP891216");
    // documents.print();

    BTree tree(3);
    tree.insert(Word("test"));
    tree.insert(Word("architecte"));
    tree.insert(Word("pleonasme"));
    tree.insert(Word("satisfaction"));
    tree.insert(Word("masks"));
    tree.insert(Word("power"));
    tree.insert(Word("original"));
    tree.insert(Word("zebra"));

    tree.traverse();

    Word word("satisfaction");
    (tree.search(word) != nullptr)? std::cout << "\nPresent" : std::cout << "\nNot Present";

    Word word_("void");
    (tree.search(word_) != nullptr)? std::cout << "\nPresent" : std::cout << "\nNot Present";

    return 0;
}
