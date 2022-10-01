#pragma once
#include "BTreeNode.hh"
#include <string>

class BTree {
private:
    std::string _number;
    BTreeNode *_root;
    int _minDegree;

public:
    explicit BTree(int minDegree);

    void traverse();
    BTreeNode* search(const Word& word);
    void insert(const Word& word);
};
