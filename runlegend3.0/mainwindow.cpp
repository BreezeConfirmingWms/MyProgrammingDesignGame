#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"myrunwidget.h"
#include"mybutton.h"
#include<QPaintEvent>
#include<QPainter>
#include<QPushButton>
#include<QMessageBox>
#include<QMenu>
#include<QMenuBar>
#include<QSound>

#define butn1 ":/new/img/btn1.png"
#define butn2 ":/new/img/btn2.png"
#define butn3 ":/new/img/btn3.png"
#define butn4 ":/new/img/btn4.png"
#define butn5 ":/new/img/btn5.png"
#define butn6 ":/new/img/btn6.png"
#define butn7 ":/new/img/btn7.png"
#define butn8 ":/new/img/btn8.png"
#define title ":/new/img/title.png"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1680,1050);
    this->setWindowIcon(QPixmap(title));
    this->setWindowTitle("myRUNlegend");
    game_widget=new gamewidget(this,this->width(),this->height());
    gtn1=new gameButton(butn1,butn2);
    gtn1->setParent(this);
    gtn1->move(1000,400);

    gtn2=new gameButton(butn3,butn4);
    gtn2->setParent(this);
    gtn2->move(800,425);
    QString strtail="游戏玩法:\n"
"1.点击开始进入游戏\n"
"2.游戏以控制角色避开障碍物，吃到尽可能多金币或魔晶为目标\n"
"3.控制角色跑动越远得分越高，吃到金币或魔晶会有加分，碰到障碍物会扣分\n"
"4.吃到红心会加速回血，吃到法杖会暂时消除所有障碍物\n"
"5.不碰到障碍物人物会自动缓慢回血，血条为空时游戏结束\n"
"6.游戏会自动记录你最高记录，不断挑战吧！";
                     connect(gtn2,&QPushButton::clicked,this,
                             [=](){
                         QMessageBox::about(this,"游戏玩法",strtail);
                     }
                             );
 gtn3=new gameButton(butn5,butn6);
 gtn3->setParent(this);
 gtn3->move(600,425);
 QString strex="按 键 操 作 :\n"
                    "   1.按下W键控制角色向上跳跃，在空中可进行二次跳跃。\n"
                    "   2.按下S键控制角色加速下落。\n"
                    "   3.按下A键控制角色向左加速移动。\n"
                    "   4.按下D键控制角色向右加速。\n"
                    "   5.游戏中按下esc键暂停游戏，再次按下esc键继续游戏。\n"
                    "   6.游戏结束后按下R键重新开始游戏，按下B键返回游戏主菜单。";
 connect(gtn3,&QPushButton::clicked,this,
         [=](){
     QMessageBox::about(this,"操作方法",strex);
 }
         );
 gtn4=new gameButton(butn7,butn8);
 gtn4->setParent(this);
 gtn4->move(400,425);

 connect(gtn4,&QPushButton::clicked,this,
         [=](){
     QString strend="你的最高分数为:"+QString("%1分").arg(game_widget->maxscore);
     QMessageBox::about(this,"最高记录",strend);
 }
         );
 connect(gtn1,&QPushButton::clicked,this,
         [=](){
                  start=new QPropertyAnimation(gtn1,"geometry");
                  start->setDuration(300);
                  start->setEasingCurve(QEasingCurve::OutQuad);
                  start->setStartValue(QRect(gtn1->x(),gtn1->y(),gtn1->width(),gtn1->height()));
                  start->setEndValue(QRect(gtn1->x(),750,gtn1->width(),gtn1->height()));
                  start->start();
                  game_widget->isRuning=true;
                  game_widget->but1=gtn1;
                  game_widget->but2=gtn2;
                  game_widget->but3=gtn3;
                  game_widget->but4=gtn4;
                  game_widget->start_game();
                  gtn1->hide();
                  gtn2->hide();
                  gtn3->hide();
                  gtn4->hide();
 }
         );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gtn1;
    delete start;
    delete game_widget;
}

