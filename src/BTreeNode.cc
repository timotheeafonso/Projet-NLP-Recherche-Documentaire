#include "BTreeNode.hh"
#include <iostream>

BTreeNode::BTreeNode(int minDegree, bool leaf) {
    _minDegree = minDegree;
    _leaf = leaf;
    _degree = 0;
}

std::vector<Word>::iterator BTreeNode::getWordIterator(const int& i) {
    auto it = _words.begin();
    for (int j = 0; j < i; ++j)
        it++;

    return it;
}

std::vector<BTreeNode>::iterator BTreeNode::getNodeIterator(const int& i) {
    auto it = _childs.begin();
    for (int j = 0; j < i; ++j)
        it++;

    return it;
}

void BTreeNode::insertNonFull(const Word& word) {
    // Initialize index as index of rightmost element
    int i = _degree-1;
    auto it = _words.end();
    it--;

    // If this is a leaf node
    if (_leaf) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater words to one place ahead
        if (i >= 0 && _words[i]._word > word._word) {
            _words.push_back(_words[i]);

            it = _words.end();
            it--;

            while (i >= 0 && _words[i]._word > word._word) {
                //_words[i+1] = _words[i];
                *it = _words[i];
                i--;
                it--;
            }
        }


        // Insert the new key at found location
        //_words[i+1] = word;
        *it = word;
        _degree = _degree+1;
    }
        // If this node is not leaf
        // Find the child which is going to have the new word
    else {
        while (i >= 0 && _words[i]._word > word._word)
            i--;

        // See if the found child is full
        if (_childs[i+1]._degree == 2*_minDegree-1) {
            // If the child is full, then split it
            splitChild(i+1, _childs[i+1]);

            // After split, the middle word of childs[i] goes up and
            // childs[i] is splitted into two.  See which of the two
            // is going to have the new word
            if (_words[i]._word < word._word)
                i++;
        }
        // Increment the occurence of a word if it's already in the tree
        if (_words[i]._word == word._word)
            _words[i].incremmentOccurence();
        else
            _childs[i+1].insertNonFull(word);
    }
}

void BTreeNode::splitChild(int i, BTreeNode child) {
    // Create a new node which is going to store (t-1) words
    // of child
    BTreeNode z(child._minDegree, child._leaf);
    z._degree = _minDegree - 1;

    // Copy the last (t-1) words of child to z
    for (int j = 0; j < _minDegree-1; j++) {
        //z._words[j] = child._words[j+_minDegree];
        z._words.push_back(child._words[j+_minDegree]);
    }

    // Copy the last t children of child to z
    if (!child._leaf) {
        for (int j = 0; j < _minDegree; j++) {
            //z._childs[j] = child._childs[j+_minDegree];
            auto it = z._childs.begin();
            *it = child._childs[j+_minDegree];
            it++;
        }
    }

    // Reduce the number of words in child
    child._degree = _minDegree - 1;

    // Since this node is going to have a new child,
    // create space of new child
    auto itN = getNodeIterator(_degree);
    for (int j = _degree; j >= i+1; j--) {
        if (j == _degree) {
            _childs.push_back(_childs[j]);
            itN--;
            j--;
        }
        //_childs[j+1] = _childs[j];
        *++itN = _childs[j];
        itN--;
    }

    // Link the new child to this node
    // _childs[i+1] = z;
    *itN = z;

    // A key of child will move to this node. Find the location of
    // new key and move all greater words one space ahead
    auto itW = getWordIterator(_degree-1);
    for (int j = _degree-1; j >= i; j--) {
        if (j == _degree-1) {
            _words.push_back(_words[j]);
            itW--;
            j--;
        }
        //_words[j + 1] = _words[j];
        *itW = _words[j];
        itW--;
    }

    // Copy the middle key of child to this node
    //_words[i] = child._words[_minDegree-1];
    if (_words.empty())
        _words.push_back(child._words[_minDegree-1]);
    else {
        itW = getWordIterator(i);
        *itW = child._words[_minDegree-1];
    }

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
            _childs[i].traverse();
        std::cout << "\n" << _words[i]._word << " : " << _words[i]._occurence;
    }

    // Print the subtree rooted with last child
    if (!_leaf)
        _childs[i].traverse();
}

/*BTreeNode BTreeNode::search(const Word& word) {
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
    return _childs[i].search(word);
}*/