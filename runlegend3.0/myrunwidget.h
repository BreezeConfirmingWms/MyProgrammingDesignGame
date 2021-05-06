#ifndef MYRUNWIDGET_H
#define MYRUNWIDGET_H
#include<QWidget>
#include<QTimer>
#include<vector>
#include "barriers.h"
#include "mybutton.h"
#include "shrad-dlg.h"

using namespace std;
class hero;
class gamewidget:public QWidget{
    Q_OBJECT
private:
    QPixmap background[3];
    QPixmap initstart;
    QPixmap ground;
    QPixmap pauseimg;
    hero*r=NULL;
    int hurtfbc;
    QPixmap hurtimg;
    QPixmap gameoverimg;
public:
   ~gamewidget();

    gamewidget(QWidget*parent=nullptr,int wid=1680 ,int hei=1050);
    vector<Wall*>bar1;
    vector<coin*>bar2;
    vector<arrow*>bar3;
    vector<mbottle*>bar4;
    vector<Ascepter*>bar5;
    vector<circle*>bar6;
    vector<bequest*>bar8;
    vector<goblin*>bar9;
    vector<magicalbook*>bar10;
    vector<monky*>barmon;
    vector<demo*>bardemo;
    vector<bomb*>barbmb;

    gameButton *but1=NULL;
    gameButton *but2=NULL;
    gameButton *but3=NULL;
    gameButton *but4=NULL;



    double backImgX[3]={0,200,0};
       double imgSpeed[3]={0.15,1,0.5};
       double ground_X;
       double ground_speed;
       int ground_Y;
       bool isRuning;
       bool isPause;
       bool GameOver=false;
       bool beforegame;
       bool up;
       bool down;
       bool right;
       bool left ;
       bool shradjug=0;
       int Coinnum ;
       int Score;
       double difficult;
       int rscore=0;
       bool rtn=0;
       int cnt=0,tmp=0;
       int*roler=new int[50];
       QTimer remove;
           void paintEvent(QPaintEvent*);
             void start_game();
             void keyPressEvent(QKeyEvent *event);
             void keyReleaseEvent(QKeyEvent *event);
             void addBarriers();
             void gamepause();
             void gamecontinue();
             void dashmove();
             void gameIsOver();
             void restart();
             void back();
             void shradpause();
             int maxscore ;
     signals:

public slots:
        void recievedata(int a,int b,int*d,bool c);

};

#endif // MYRUNWIDGET_H
