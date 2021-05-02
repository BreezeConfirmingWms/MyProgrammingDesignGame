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
    QPixmap background[5];
    QPixmap initstart;
    QPixmap ground;
    QPixmap pauseimg;
    hero*r=NULL;
    int hurtfbc;
    QPixmap hurtimg;
    QPixmap gameoverimg;
public:
   ~gamewidget();

    explicit gamewidget(QWidget *parent = nullptr,int wid=1650,int hei=1000);
    vector<Wall*>bar1;
    vector<coin*>bar2;
    vector<arrow*>bar3;
    vector<mbottle*>bar4;
    vector<Ascepter*>bar5;
    vector<circle*>bar6;
    vector<shrad*>bar7;
    vector<bequest*>bar8;
    vector<goblin*>bar9;
    vector<magicalbook*>bar10;

    gameButton *but1=NULL;
    gameButton *but2=NULL;
    gameButton *but3=NULL;
    gameButton *but4=NULL;

    double backImgX[5]={150,200,250,300,325};
       double imgSpeed[5]={0.15,0.3,0.5,0.75,1};
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
       int Coinnum ;
       int Score;
       double difficult;
       QTimer remove;
           void paintEvent(QPaintEvent*);
             void start_game();
             void keyPressEvent(QKeyEvent *event);
             void keyReleaseEvent(QKeyEvent *event);
             void addBarriers();
             void addshrad(bequest*bq);
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

};

#endif // MYRUNWIDGET_H
