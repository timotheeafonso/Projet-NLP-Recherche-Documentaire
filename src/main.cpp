#include <iostream>
#include "Document.hh"
#include "Documents.hh"
#include "Query.hh"
#include "BTrees.hh"
#include "BTree.hh"
#include "Word.hh"

#include "mainwindow.hh"
#include "../build/ui_mainwindow.h"



int main(int argc, char *argv[]) {
    Documents documents;
    documents.parse("../AP/AP891216");
    //documents.print();
    char str[] ="The inventor of an about ultrasonic gun used to stun racehorses was sentenced Thursday to 14 years in jail for his involvement in a multimillion dollar cocaine ring. Southwark Crown Court Judge Gerald Butler also ordered assets of auto dealer James Laming worth $38,320 be confiscated or Laming,49, would face an additional 18 months in jail. A jury convicted Laming and two other men Nov. 14. Ring leader Rene Black, 35, was sentenced to 15 years for masterminding the $24.8 million cocaine operation, which included Europe's first cocaine factory.";
    std::string cleanStr=documents.deleteSpecialChar(str);    
    std::vector<std::string> mylist = documents.tokenize(cleanStr);
    std::vector<std::string> stopwords = documents.getStopword();
    mylist=documents.deleteStopwords(mylist,stopwords);
    
    for (auto it : mylist) {
        std::cout << it << std::endl;
    }
    // documents.print();

    BTrees trees;
    trees.addTrees(documents, 3);

    /*BTree tree(3);

    for (int i = 0; i < 7; ++i) {
        tree.insert(Word("test"));
    }*/

    /*tree.insert(Word("test"));
    tree.insert(Word("architecte"));
    tree.insert(Word("pleonasme"));
    tree.insert(Word("satisfaction"));
    tree.insert(Word("masks"));
    tree.insert(Word("power"));
    tree.insert(Word("original"));
    tree.insert(Word("zebra"));
    tree.insert(Word("pleonasme"));*/

    /*tree.traverse();

    Word word("satisfaction");
    (tree.search(word) != nullptr)? std::cout << "\nPresent" : std::cout << "\nNot Present";

    Word word_("void");
    (tree.search(word_) != nullptr)? std::cout << "\nPresent" : std::cout << "\nNot Present";*/


    mylist=documents.stem(mylist);    
    
    for (auto it : mylist) {
            std::cout << it << std::endl;
    }
    
    
    std::string q="Hors in mountin with blue skye";
    Query query(q);
    query.correctQuery();
    
    QApplication app{argc, argv};
    MainWindow ui;
    ui.show();
    return app.exec();
}
