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
    ui->label->setVisible(false);
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text() != ""){
        ui->listWidget->clear();
        std::cout<<"1"<<std::endl;
        QString str = ui->lineEdit->text();
        Query query(str.toStdString());
        std::string str2=query.correctQuery();
        std::string correct="Showing results for: ";
        if(str.toStdString()!=str2){
            correct+=str2;
            ui->label->setVisible(true);
            ui->pushButton_2->setVisible(true);
            ui->pushButton_2->setText(QString::fromStdString(str2));
        }

        Documents documents;
        documents.parse("../AP/AP891216");
        Forest forest;
        forest.createForest(documents, 3);

        std::vector<std::string> listTop10=query.getTopX(forest,10);
        Document ldoc [10]={};
        for(Document doc: documents.getDocuments()){
            bool inTopX=false;
            int index=0;
            for(auto nb : listTop10){

                if(nb==doc.getNumber()){
                    inTopX=true;
                }
                if(!inTopX){
                    index++;
                }
            }
            if(inTopX){
                ldoc[index]=doc;
            }
        }

        int i=0;
        std::string tt;
        for(auto d : ldoc){
            std::cout<<d.getNumber()<<"\n";
            tt=d.getNumber();
            for(std::string title : d.getTitle()){
                tt+=" "+title;
            }
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText(QString::fromStdString(tt));
            ui->listWidget->insertItem(i, newItem);
            i++;
        }
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->pushButton_2->text());
    ui->pushButton_2->setVisible(false);
    ui->label->setVisible(false);
    ui->listWidget->clear();
    this->on_pushButton_clicked();

}




