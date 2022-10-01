#pragma once
#include <string>

class Word {
friend class BTree;
friend class BTreeNode;

private:
    std::string _word;
    unsigned int _occurences;

public:
    Word();
    Word(std::string word);

};
