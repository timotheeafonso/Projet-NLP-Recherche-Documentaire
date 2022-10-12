#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include "Document.hh"
#include "Documents.hh"
#include "Query.hh"
#include "Forest.hh"
#include "BTree.hh"
#include "Word.hh"

#include "mainwindow.hh"
#include "../build/ui_mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    MainWindow ui;
    ui.show();
    return app.exec();
}
