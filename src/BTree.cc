#include "BTree.hh"

BTree::BTree(int minDegree):
    _root(BTreeNode(minDegree, true)),
    _minDegree(minDegree) {}

void BTree::traverse() {
    if (_root._degree)
        _root.traverse();
}

int BTree::search(const std::string& word) {
    if (_root._degree == 0)
        return 0;
    else
        return _root.search(word);
}

void BTree::insert(const Word &word) {
    // If tree is empty
    if (_root._degree == 0) {
        // Allocate memory for root
        _root._words.push_back(word);  // Insert key
        _root._degree = 1;  // Update number of words in root
    }
    else { // If tree is not empty
        // If root is full, then tree grows in height
        if (_root._degree == 2*_minDegree-1 && _root._children.empty())
        {
            // Allocate memory for new root
            BTreeNode node(_minDegree, false);

            // Make old root as child of new root
            //node._children[0] = _root;
            node._children.push_back(_root);


            // Split the old root and move 1 key to the new root
            node.splitChild(0, _root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (node._words[0]._word < word._word)
                i++;
            node._children[i].insertNonFull(word);

            // Change root
            _root = node;
        }
        else  // If root is not full, call insertNonFull for root

            _root.insertNonFull(word);
    }
}