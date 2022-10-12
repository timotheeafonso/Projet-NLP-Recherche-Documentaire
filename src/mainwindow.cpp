#include "mainwindow.hh"
#include "../build/ui_mainwindow.h"
#include <iostream>
#include "Document.hh"
#include "Documents.hh"
#include "Query.hh"
#include <QListWidgetItem>
#include <QTextEdit>
 
 
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_2->setVisible(false);
    ui->label->setVisible(false);

    documents.parse("../AP/AP891216");
    forest.createForest(documents, 3);

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
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText(QString::fromStdString(d.getOriginalTitle()));
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
    QVBoxLayout *verticalLayout2;

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

    centralwidget2->show();

}



