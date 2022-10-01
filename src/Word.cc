#include "Word.hh"

Word::Word() {

}

Word::Word(std::string word) {
    _word = word;
    _occurences = 1;
}

