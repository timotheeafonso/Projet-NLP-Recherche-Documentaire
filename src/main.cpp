#include <iostream>
#include "Document.hh"
#include "Documents.hh"
#include "BTrees.hh"
#include "BTree.hh"
#include "Word.hh"

int main() {
    Documents documents;
    documents.parse("../AP/AP891216");
    // documents.print();

    BTrees trees;
    trees.addTrees(documents, 3);

    /*BTree tree(3);

    for (int i = 0; i < 7; ++i) {
        tree.insert(Word("test"));
    }*/

    /*tree.insert(Word("test"));
    tree.insert(Word("architecte"));
    tree.insert(Word("pleonasme"));
    tree.insert(Word("satisfaction"));
    tree.insert(Word("masks"));
    tree.insert(Word("power"));
    tree.insert(Word("original"));
    tree.insert(Word("zebra"));
    tree.insert(Word("pleonasme"));*/

    /*tree.traverse();

    Word word("satisfaction");
    (tree.search(word) != nullptr)? std::cout << "\nPresent" : std::cout << "\nNot Present";

    Word word_("void");
    (tree.search(word_) != nullptr)? std::cout << "\nPresent" : std::cout << "\nNot Present";*/

    return 0;
}
