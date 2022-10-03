#pragma once
#include "Word.hh"
#include <string>
#include <vector>

class BTreeNode {
friend class BTree;

private:
    std::vector<Word> _words;
    std::vector<BTreeNode> _childs;
    int _minDegree;
    int _degree;
    bool _leaf;

public:
    BTreeNode(int minDegree, bool leaf);

    void insertNonFull(const Word& word);
    void splitChild(int i, BTreeNode child);
    void traverse();
    //BTreeNode search(const Word& word);
};
