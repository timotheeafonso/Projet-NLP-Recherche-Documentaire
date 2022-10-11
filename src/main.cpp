#include <iostream>
#include "Document.hh"
#include "Documents.hh"
#include "Query.hh"
#include "Forest.hh"
#include "BTree.hh"
#include "Word.hh"

#include "mainwindow.hh"
#include "../build/ui_mainwindow.h"

int main(int argc, char *argv[]) {
    Documents documents;
    documents.parse("../AP/AP891216");

    Forest forest;
    forest.createForest(documents, 3);
    
    std::string q="the job of chief of government";
    Query query(q);
    query.correctQuery();
    query.getTopX(forest,10);

    QApplication app{argc, argv};
    MainWindow ui;
    ui.show();
    return app.exec();
}
