#include "mainwindow.hh"
#include "../build/ui_mainwindow.h"
#include <iostream>
#include "Document.hh"
#include "Documents.hh"
#include "Query.hh"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_2->setVisible(false);
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    Query query(str.toStdString());
    std::string str2=query.correctQuery();
    std::string correct="Showing results for: ";
    if(str.toStdString()!=str2){
        correct+=str2;
        ui->pushButton_2->setVisible(true);
        ui->pushButton_2->setText(QString::fromStdString(correct));
    }

    Documents documents;
    documents.parse("../AP/AP891216");
    int i=0;
    std::string tt;
    for(Document doc: documents.getDocuments()){
        tt="";
        for(std::string title : doc.getTitle()){
            tt+=" "+title;
        }
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::fromStdString(tt));
        ui->listWidget->insertItem(i, newItem);
        i++;
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->pushButton_2->text());
    ui->pushButton_2->setVisible(false);
}




