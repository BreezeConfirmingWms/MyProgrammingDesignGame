#ifndef HERO_H
#define HERO_H
#include<QWidget>
#include"myrunwidget.h"
#include"barriers.h"
#include<QTimer>
class hero:public QWidget{
 Q_OBJECT
private:
gamewidget*game;
QPixmap runimg[5];
QPixmap jump_img;
int curjogimg;
int wid,hei,x,y;
int hp,hpmax;
int currunimg=0;
int score=0;
public:
hero(gamewidget*game);
QTimer runtimer;
QTimer jumptimer;
QTimer hptimer;

bool jumponce,jumptwice;
bool fallstate,twicerdy;
double fallspeed,fallspeed_a,jumpspeed;
int jumph;
int getx();
int gety();
int getwid();
int gethei();
int getscore();
void setscore(int n);
void move(bool up,bool down,bool right,bool left);
QPixmap getimg();
void pausehero();
void continuehero();
void reducehp();
void increasehp(int b);
int gethp(),getcurhpcnt();

void dashmove();
void shrandmove();

void addscore(int s);
signals:
public slots:
};

#endif // HERO_H
