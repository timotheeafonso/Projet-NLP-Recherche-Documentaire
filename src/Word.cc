#include <utility>

#include "Word.hh"

Word::Word(std::string word) {
    _word = std::move(word);
    _occurence = 1;
}
