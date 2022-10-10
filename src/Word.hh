#pragma once
#include <string>

class Word {
friend class BTree;
friend class BTreeNode;

private:
    std::string _word;
    unsigned int _occurence;

    void incremmentOccurence() { _occurence++; };

public:
    Word()=default;;
    explicit Word(std::string word);
};
