#include "BTreeNode.hh"
#include <iostream>

BTreeNode::BTreeNode(int minDegree, bool leaf) {
    _minDegree = minDegree;
    _leaf = leaf;
    _degree = 0;

    _words = new Word[2*_minDegree-1];
    _childs = new BTreeNode*[2*_minDegree];
}

void BTreeNode::insertNonFull(const Word& word) {
    // Initialize index as index of rightmost element
    int i = _degree-1;

    // If this is a leaf node
    if (_leaf) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater words to one place ahead
        while (i >= 0 && _words[i]._word > word._word) {
            _words[i+1] = _words[i];
            i--;
        }

        // Insert the new key at found location
        _words[i+1] = word;
        _degree = _degree+1;
    }
    // If this node is not leaf
    // Find the child which is going to have the new key
    else {
        while (i >= 0 && _words[i]._word > word._word)
            i--;

        // See if the found child is full
        if (_childs[i+1]->_degree == 2*_minDegree-1) {
            // If the child is full, then split it
            splitChild(i+1, _childs[i+1]);

            // After split, the middle key of childs[i] goes up and
            // childs[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (_words[i]._word < word._word)
                i++;
        }
        _childs[i+1]->insertNonFull(word);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *child) {
    // Create a new node which is going to store (t-1) words
    // of child
    auto *z = new BTreeNode(child->_minDegree, child->_leaf);
    z->_degree = _minDegree - 1;

    // Copy the last (t-1) words of child to z
    for (int j = 0; j < _minDegree-1; j++)
        z->_words[j] = child->_words[j+_minDegree];

    // Copy the last t children of child to z
    if (!child->_leaf) {
        for (int j = 0; j < _minDegree; j++)
            z->_childs[j] = child->_childs[j+_minDegree];
    }

    // Reduce the number of words in child
    child->_degree = _minDegree - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = _degree; j >= i+1; j--)
        _childs[j+1] = _childs[j];

    // Link the new child to this node
    _childs[i+1] = z;

    // A key of child will move to this node. Find the location of
    // new key and move all greater words one space ahead
    for (int j = _degree-1; j >= i; j--)
        _words[j+1] = _words[j];

    // Copy the middle key of child to this node
    _words[i] = child->_words[_minDegree-1];

    // Increment count of words in this node
    _degree = _degree + 1;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse() {
    // There are degree words and degree+1 children, traverse through degree words
    // and first degree children
    int i;
    for (i = 0; i < _degree; i++) {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child childs[i].
        if (!_leaf)
            _childs[i]->traverse();
        std::cout << " " << _words[i]._word << " : " << _words[i]._occurences;
    }

    // Print the subtree rooted with last child
    if (!_leaf)
        _childs[i]->traverse();
}

BTreeNode *BTreeNode::search(const Word& word) {
    // Find the first key greater than or equal to word
    int i = 0;
    while (i < _degree && word._word > _words[i]._word)
        i++;

    // If the found key is equal to word, return this node
    if (_words[i]._word == word._word)
        return this;

    // If key is not found here and this is a leaf node
    if (_leaf)
        return nullptr;

    // Go to the appropriate child
    return _childs[i]->search(word);
}
