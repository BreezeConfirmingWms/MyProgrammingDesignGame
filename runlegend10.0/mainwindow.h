#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include"mybutton.h"
#include"myrunwidget.h"
#include<QPropertyAnimation>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    gameButton*gtn1=NULL;
    gameButton*gtn2=NULL;
    gameButton*gtn3=NULL;
    gameButton*gtn4=NULL;
    gamewidget*game_widget=NULL;
    QPropertyAnimation*start=NULL;

private slots:

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
