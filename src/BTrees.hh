#pragma once
#include <vector>
#include "BTree.hh"
#include "Documents.hh"

class BTrees {
private:
    std::vector<BTree> _trees;

public:
    BTrees()=default;;

    void addTrees(Documents& documents, const int& order);
};
