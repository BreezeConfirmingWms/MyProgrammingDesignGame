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
"3.控制角色跑动越远得分越高，吃到金币会有加分，碰到障碍物会扣分和减速\n"
"4.吃到红心会加速回血，吃到法杖会暂时消除所有障碍物\n"
"5.不碰到障碍物人物会自动缓慢回血，血条为空时游戏结束\n"
"6.游戏会自动记录你最高记录，不断挑战吧！\n"
"一些特别说明:\n"
"·圣者遗迹模式下会弹出对话框，需要你按亡语中规定的左右步数信息挑选魔晶,\n"
"其能量点数在对应魔晶上方，你的目标是选择能量点数累加最大的路径，若成功，你将再次获得奖励。\n"
"·哥布林怪盗会自动选取最优博弈策略，无论你按什么顺序选取能量点数对弈都即有可能输，且每次能量点数对应你上次所选,\n"
"出现频率较高速度较快很是烦人，尽量避开他们;\n"
"·天书的背景：古老圣树上栖息着具有灾难启示能力的神猴，他们以特殊的方式相互牵拉形成法阵护佑，世人无法知到他们法阵形状\n"
"只能由智者通过天书的编号信息窥见未来，每当灾难降临，他们都会有意识在特定时间松手，以此降临人间启发世人;\n"
"每次天书都会按顺序给出之前一段时间给出神猴松手的信息，第一列为编号，第二列为松了哪只手,\n"
"1左2右。注意你眼中的天书会从上至下显示每只圣猴掉落的时间，-1表示在某个时间后仍未掉落，0表示开始即掉落，以此类推。\n"
"当掉落猴子超过总数一半时将会进入恐怖轮回，按“自然数+3乘出现次数+9”次按键后引发几乎能直接杀死你的若干次大灾难,但是勇士只要在来临前那一刻按下键盘k,\n"
"就可以阻止灾难发生，恐怖轮回将会被下次天书启示覆盖。若未超过总数一半未来预示着持续一段时间太平,会立马降临福音,接受他的引导将可以回血加分。";
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

