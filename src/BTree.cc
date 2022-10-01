#include "BTree.hh"

BTree::BTree(int minDegree) {
    _minDegree = minDegree;
    _root = nullptr;
}

void BTree::traverse() {
    if (_root)
        _root->traverse();
}

BTreeNode *BTree::search(const Word &word) {
    if (!_root)
        return _root;
    else
        return _root->search(word);
}

void BTree::insert(const Word &word) {
    // If tree is empty
    if (!_root)
    {
        // Allocate memory for root
        _root = new BTreeNode(_minDegree, true);
        _root->_words[0] = word;  // Insert key
        _root->_minDegree = 1;  // Update number of words in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (_root->_minDegree == 2*_minDegree-1)
        {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(_minDegree, false);

            // Make old root as child of new root
            s->_childs[0] = _root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, _root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->_words[0]._word < word._word)
                i++;
            s->_childs[i]->insertNonFull(word);

            // Change root
            _root = s;
        }
        else  // If root is not full, call insertNonFull for root
            _root->insertNonFull(word);
    }
}
