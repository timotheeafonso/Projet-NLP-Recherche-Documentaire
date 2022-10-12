#include "Forest.hh"
#include "Document.hh"
#include <iostream>

void Forest::createForest(Documents& documents, const int& order) {
    for (auto &doc : documents.getDocuments()) {
        BTree tree(order);
        tree.setNumber(std::move(doc.getNumber()));

        for (const auto& word : doc.getContent()) {
            tree.insert(Word(word));
        }

        tree.traverse();
        _forest.push_back(tree);
    }
}