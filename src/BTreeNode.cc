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
    auto it = _children.begin();
    for (int j = 0; j < i; ++j)
        it++;

    return it;
}

void BTreeNode::insertNonFull(const Word& word) {
    int w = wordExist(word);

    if (w != _degree) {
        _words[w].incremmentOccurence();
    }
    else {
        // Initialize index as index of rightmost element
        int i = _degree-1;

        // If this is a leaf node
        if (_leaf) {
            // The following loop does two things
            // a) Finds the location of new key to be inserted
            // b) Moves all greater words to one place ahead
            _words.push_back(_words[i]);
            auto it = _words.end();
            it--;

            while (i >= 0 && _words[i]._word > word._word) {
                //_words[i+1] = _words[i];
                *it = _words[i];
                i--;
                it--;
            }

            // Insert the new key at found location
            //_words[i+1] = word;
            *it = word;
            _degree = _degree + 1;
        }
            // If this node is not leaf
            // Find the child which is going to have the new word
        else {
            while (i >= 0 && _words[i]._word > word._word)
                i--;

            // See if the found child is full
            if (_children[i + 1]._degree == 2 * _minDegree - 1) {
                // If the child is full, then split it
                splitChild(i + 1, _children[i + 1]);

                // After split, the middle word of childs[i] goes up and
                // childs[i] is splitted into two.  See which of the two
                // is going to have the new word
                if (_words[i + 1]._word < word._word)
                    i++;
            }

            _children[i + 1].insertNonFull(word);
        }
    }
}

void BTreeNode::splitChild(int i, BTreeNode child) {
    // Create a new node which is going to store (t-1) words
    // of child
    BTreeNode node(child._minDegree, child._leaf);
    node._degree = _minDegree - 1;

    // Copy the last (_minDegree-1) words of child to node
    for (int j = 0; j < _minDegree-1; j++) {
        //node._words[j] = child._words[j+_minDegree];
        node._words.push_back(child._words[j + _minDegree]);
    }

    for (int j = 0; j < _minDegree-1; j++) {
        _children[i]._words.pop_back();
        _children[i]._degree--;
    }
    _children[i]._words.pop_back();
    _children[i]._degree--;

    // Copy the last t children of child to node
    if (!child._leaf) {
        for (int j = 0; j < _minDegree; j++) {
            //node._children[j] = child._children[j+_minDegree];
            node._children.push_back(child._children[j+_minDegree]);
        }
    }

    // Reduce the number of words in child
    child._degree = _minDegree - 1;

    // Since this node is going to have a new child,
    // create space of new child
    _children.push_back(_children[_degree]);
    auto itN = getNodeIterator(_degree);

    for (int j = _degree-1; j >= i+1; j--) {
        //_children[j+1] = _children[j];
        *itN = _children[j];
        itN--;
    }

    // Link the new child to this node
    // _children[i+1] = node;
    if (i+1 > _children.size()-1)
        _children.push_back(node);
    else {
        itN = getNodeIterator(i + 1);
        *itN = node;
    }

    // Add the word if the node has none of them
    if (_words.empty())
        _words.push_back(child._words[_minDegree-1]);
    else {
        // A key of child will move to this node. Find the location of
        // new key and move all greater words one space ahead
        _words.push_back(_words[_degree-1]);
        auto itW = getWordIterator(_degree-1);

        for (int j = _degree-2; j >= i; j--) {
            //_words[j + 1] = _words[j];
            *itW = _words[j];
            itW--;
        }

        // Copy the middle key of child to this node
        //_words[i] = child._words[_minDegree-1];
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
            _children[i].traverse();
        std::cout << "\n" << _words[i]._word << " : " << _words[i]._occurence;
    }

    // Print the subtree rooted with last child
    if (!_leaf)
        _children[i].traverse();
}

int BTreeNode::wordExist(const Word &word) {
    int i = 0;
    for (i; i < _degree; ++i) {
        if (word._word == _words[i]._word)
            return i;
    }

    return i;
}

int BTreeNode::search(const std::string& word) {
    // Find the first key greater than or equal to word
    int i = 0;
    while (i < _degree && word > _words[i]._word)
        i++;

    // If the found key is equal to word, return this node
    if (_words[i]._word == word)
        return _words[i]._occurence;

    // If key is not found here and this is a leaf node
    if (_leaf)
        return 0;

    // Go to the appropriate child
    return _children[i].search(word);
}
