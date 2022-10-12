#pragma once
#include <vector>
#include "BTree.hh"
#include "Documents.hh"

class Forest {
private:
    std::vector<BTree> _forest;

public:
    Forest()=default;;
    std::vector<BTree> getForest() { return _forest; }

    void createForest(Documents& documents, const int& order);
};
