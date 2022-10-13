#include "mainwindow.hh"
#include "../build/ui_mainwindow.h"
#include <iostream>
#include "Document.hh"
#include "Documents.hh"
#include "Query.hh"
#include <QListWidgetItem>
#include <QTextEdit>
#include <dirent.h>
#include <string>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_2->setVisible(false);
    ui->label->setVisible(false);
   
    std::string path = "../AP";

    DIR *dir; struct dirent *diread;

    if ((dir = opendir("../AP")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            if(diread->d_name[0]=='A'){
                std::string file=path+"/"+diread->d_name;
                // std::cout<<file<<std::endl;
                documents.parse(file);
            }

        }
        closedir (dir);
    }

    forest.createForest(documents, 3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    int ind=str.toStdString().size()-1;
    int choix=0;
    if(str != ""){
        if(str.toStdString()[0]=='\"' && str.toStdString()[ind]=='\"'){
            choix=1;
            str.remove(0, 1); 
            str.remove(ind-1, 1); 
            // std::cout<<str.toStdString()<<std::endl;
        }
        ui->listWidget->clear();
        
        Query query(str.toStdString());
        std::string str2=query.correctQuery();
        if(str.toStdString()!=str2){
            ui->label->setVisible(true);
            ui->pushButton_2->setVisible(true);
            ui->pushButton_2->setText(QString::fromStdString(str2));
        }

        int i=0;
        if(choix==1){
                std::string lowerQuerry= str.toStdString();
                for(char c : lowerQuerry){
                    if (isupper(c)){
                        char lower = c + 32;
                        std::replace(lowerQuerry.begin(), lowerQuerry.end(), c, lower);
                    }
                }
                for(Document doc: documents.getDocuments()){
                    std::string lowerContent=doc.getOriginalContent();
                     for(char c : lowerContent){
                        if (isupper(c)){
                            char lower = c + 32;
                            std::replace(lowerContent.begin(), lowerContent.end(), c, lower);
                        }
                     }
                    if ((lowerContent).find(lowerQuerry) != std::string::npos ){
                        begin.push_back((lowerContent).find(lowerQuerry));
                        end.push_back(str.toStdString().size());
                        QListWidgetItem *newItem = new QListWidgetItem;
                        newItem->setText(QString::fromStdString(doc.getOriginalTitle()));
                        ui->listWidget->insertItem(i, newItem);
                        i++;
                    } 
                }
        }else{
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
                for(auto d : ldoc){
                    // std::cout<<d.getNumber()<<"\n";
                    QListWidgetItem *newItem = new QListWidgetItem;
                    newItem->setText(QString::fromStdString(d.getOriginalTitle()));
                    ui->listWidget->insertItem(i, newItem);
                    i++;
                }
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

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

    QLabel *labelText;
    QLabel *labelNumber;
    QLabel *labelAuteur;
    QTextEdit *text;
    QLabel *number;
    QLabel *author;
    QWidget *centralwidget2;
    QWidget *verticalLayoutWidget2;

    centralwidget2 = new QWidget();
    centralwidget2->setObjectName(QString::fromUtf8("Window 2"));
    verticalLayoutWidget2 = new QWidget(centralwidget2);
    verticalLayoutWidget2->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget2->setGeometry(QRect(0, 0, 800, 600));
    centralwidget2->resize(800,600);

    labelNumber = new QLabel(verticalLayoutWidget2);
    labelNumber->setObjectName(QString::fromUtf8("labelNumber"));
    labelNumber->setText("Number :");
    labelNumber->setGeometry(QRect(20, 20, 89, 28));

    labelText = new QLabel(verticalLayoutWidget2);
    labelText->setObjectName(QString::fromUtf8("label2"));
    labelText->setText("Text :");
    labelText->setGeometry(QRect(20, 80, 89, 28));

    labelAuteur = new QLabel(verticalLayoutWidget2);
    labelAuteur->setObjectName(QString::fromUtf8("labelAuteur"));
    labelAuteur->setText("Author :");
    labelAuteur->setGeometry(QRect(20, 430, 89, 28));

    number = new QLabel(verticalLayoutWidget2);
    number->setObjectName(QString::fromUtf8("number"));
    number->setGeometry(QRect(150, 20, 581, 28));

    text = new QTextEdit(verticalLayoutWidget2);
    text->setObjectName(QString::fromUtf8("text"));
    text->setGeometry(QRect(20, 120, 741, 241));

    author = new QLabel(verticalLayoutWidget2);
    author->setObjectName(QString::fromUtf8("author"));
    author->setGeometry(QRect(120, 430, 641, 28));

    QString str = item->text();
    for(Document doc: documents.getDocuments()){
        if(doc.getOriginalTitle()==str.toStdString()){
            number->setText(QString::fromStdString(doc.getNumber()));
            text->setText(QString::fromStdString(doc.getOriginalContent()));
            author->setText(QString::fromStdString(doc.getAuthor()));

        }
    }

    
    

    QTextCharFormat fmt;
    fmt.setBackground(Qt::gray);

    QTextCursor cursor(text->document());
    cursor.setPosition(begin[ui->listWidget->row(item)], QTextCursor::MoveAnchor);
    cursor.setPosition(begin[ui->listWidget->row(item)]+end[ui->listWidget->row(item)], QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);
    centralwidget2->show();

}



