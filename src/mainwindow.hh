#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QListWidgetItem> 
#include "Forest.hh"
#include "Query.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Documents documents;
    Forest forest;
    std::vector<int> begin;
    std::vector<int> end;
    int choix;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
