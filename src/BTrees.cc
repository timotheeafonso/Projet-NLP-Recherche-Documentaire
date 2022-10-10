#include "BTrees.hh"
#include "Document.hh"
#include <iostream>

void BTrees::addTrees(Documents& documents, const int& order) {
    for (auto &doc : documents.getDocuments()) {
        BTree tree(3);
        tree.setNumber(std::move(doc.getNumber()));

        int i = 0;
        for (const auto& word : doc.getContent()) {
            if(i == 26)
                break;
            tree.insert(Word(word));
            //tree.traverse();
            //std::cout << word;
            i++;
        }

        i = 0;
        for (const auto& word : doc.getContent()) {
            if(i >= 26) {
                tree.insert(Word(word));
                //std::cout << word;
            }
            i++;
        }

        tree.traverse();
        _trees.push_back(tree);
        break;
    }
}