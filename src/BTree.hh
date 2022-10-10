#pragma once
#include "BTreeNode.hh"
#include <string>

class BTree {
    friend class BTrees;

private:
    std::string _number;
    BTreeNode _root;
    int _minDegree;

public:
    explicit BTree(int minDegree);

    void setNumber(std::string number) { _number = std::move(number); };

    void traverse();
    void insert(const Word& word);
    int search(const std::string& word);
};