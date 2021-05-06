#include"hero.h"
#include"myrunwidget.h"
#include"barriers.h"
#include<QTimer>
#include<QDebug>
#include<iostream>
#define run1 ":/new/img/run1.png"
#define run2 ":/new/img/run2.png"
#define run3 ":/new/img/run3.png"
#define run4 ":/new/img/run4.png"
#define jump ":/new/img/jump.png"
using namespace std;

hero::hero(gamewidget*game){
    this->hp=3600;
    this->hpmax=3600;
    this->game=game;
    this->wid=60;
    this->hei=80;
    this->x=70;
    this->y=105;
    jumponce=jumptwice=false;
    twicerdy=false;
    fallstate=false;
    jumph=100;
    fallspeed=0;
    jumpspeed=20;
    fallspeed_a=0.5;
    jumptimer.setInterval(400);
    jumptimer.setSingleShot(true);
    for(int i=0;i<=3;i++){
        runimg[i].load(QString(":/new/img/run%1.png").arg(i+1));
    }
    jump_img.load(jump);
    curjogimg=0;
    runtimer.setInterval(100);
    connect(&runtimer,&QTimer::timeout,
               [=]()
               {
                  curjogimg=(curjogimg+1)%3;

               }
         );
    hptimer.setInterval(20);
    connect(&hptimer,&QTimer::timeout,
            [=](){
        if(hp<hpmax){
            hp+=1;
        }
    }
    );


}
void hero::move(bool up, bool down, bool right, bool left){
    if(this->y==610){
        twicerdy=true;
        fallspeed=0;
    }
    if(up){
        if(this->y==610){
        jumptimer.start();
        jumponce=false;
        }
        if(this->y<610&&twicerdy&&jumponce){
            jumptimer.start();
            fallspeed=0;
            twicerdy=false;
        }
        if(jumptimer.isActive()){
            this->y-=jumpspeed*jumptimer.remainingTime()/400;
        }
    }
    else{
        jumptimer.stop();
        jumponce=true;
    }
    this->y+=fallspeed;
    if(this->y>610)
        this->y=610;
    if(this->y<200)
        this->y=200;
    if(this->x<100)
        this->x=100;
    if(this->x>1300)
        this->x=1300;
    if(!jumptimer.isActive()){
        fallspeed+=fallspeed_a;
    }
    else
        fallspeed=0;
    if(down){
        if(this->y<610&&!jumptimer.isActive())
            fallspeed+=2*fallspeed_a;
    }
    if(right)
        this->x+=10;
    else
        this->x-=1;
    if(left)
        this->x-=10;
    else
        this->x-=1;
    this->score++;
}
int hero::getx(){
    return this->x;
}
int hero::gety(){
    return this->y;
}
int hero::getwid(){
    return this->wid;
}
int hero::gethei(){
    return this->hei;
}
void hero::setscore(int n){
    this->score+=n;
}
int hero::getscore(){
    return this->score;
}
QPixmap hero::getimg(){
    QPixmap img;
    if(this->y<610)
        img=jump_img;
    else if(this->y==610){
        img=runimg[curjogimg];
    }
    else if(this->y>610){
        img=jump_img;
    }
    return img;
}
void hero::pausehero(){
   runtimer .stop();
}
void hero::continuehero(){
    runtimer.start();
}
void hero::reducehp(){
    this->hp-=700;
    if(this->hp<=0)
        this->hp=0;
}
int hero::getcurhpcnt(){
    return this->hp*100/this->hpmax;
}
void hero::increasehp(int b){
    this->hp+=b;
    if(this->hp>this->hpmax)
        this->hp=this->hpmax;
}
void hero::dashmove(){
    x+=450;
}
void hero::addscore(int s){
    this->score+=s;
}
