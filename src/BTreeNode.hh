#pragma once
#include "Word.hh"
#include <string>
#include <vector>

class BTreeNode {
    friend class BTree;

private:
    std::vector<Word> _words;
    std::vector<BTreeNode> _children;
    int _minDegree;
    int _degree;
    bool _leaf;

public:
    BTreeNode(int minDegree, bool leaf);

    std::vector<Word>::iterator getWordIterator(const int& i);
    std::vector<BTreeNode>::iterator getNodeIterator(const int& i);

    void insertNonFull(const Word& word);
    void splitChild(int i, BTreeNode child);
    void traverse();
    int wordExist(const Word& word);
    int search(const std::string & word);
};