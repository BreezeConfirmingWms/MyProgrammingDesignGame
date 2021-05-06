#ifndef BARRIERS_H
#define BARRIERS_H

#include<QPixmap>
#include<QTimer>
#include<QPushButton>
#include<QLabel>
#include "mybutton.h"
class barriers{
private:
    int x,y;
    int width,height;
public:
    barriers(int x,int y,int width,int height);
    int getx();
    int gety();
    void setx(int x);
    void sety(int y);
    int getwidth();
    int getheight();
signals:

public slots:

};
class Wall:public barriers{
private:
    QPixmap img;
public:
    int speed;
    Wall(int x,int y,int width,int height);
    QPixmap getimg();
    bool jugcollision(int lx,int ly,int wid,int hei);
    void move();
    bool done();
};
class coin:public barriers{
private:
    QPixmap img[4];
public:
   QTimer coinout;
    int speed;
    coin(int x,int y,int width,int height);
    QPixmap getimg();
    bool jugcollision(int lx,int ly,int wid,int hei);
    void move();
    bool done();
    int cointime;
};
class mbottle:public barriers{
private:
    QPixmap img;
public:
    int speed;
    mbottle(int x,int y,int width,int height);
    QPixmap getimg();
    bool jugcollision(int lx,int ly,int wid,int hei);
    void move();
    bool done();
};
class Ascepter:public barriers{
private:
    QPixmap img;
public:
    Ascepter(int x,int y,int width,int height);
    QPixmap getimg();
    bool jugcollision(int lx,int ly,int wid,int hei);
    void move();
    bool done();
};
class arrow:public barriers{
private:
    QPixmap img;
public:
    int speed;
    arrow(int x,int y,int width,int height);
    QPixmap getimg();
    bool jugcollision(int lx,int ly,int wid,int hei);
    void move();
    bool done();
};

class circle: public barriers{
private:
    QPixmap img;
    int r;
    int collisionqwidth,collisionangle;
    bool degreeup=true;
    int degree=0;
public:
    QPixmap getimg();
    circle(int x,int y,int width,int height);
    bool jugcollision(int px,int py,int pwid,int phei);
    void move();
    bool done();
};
class bequest:public barriers{
private:
    QPixmap img;
public:
    int n,left,right;
    int num;
    int eng[35],f[35]={100},que[35],rcd[20],head=1,tail=1;
    bequest(int x,int y,int width,int height);
    bool jugcollision(int lx,int ly,int wid,int hei);
    QPixmap getimg();
    void move();
    bool done();
    void bqrand();
    int prize();
    void udt();
    void insert(int i);
    int  quefind(int x);
};
class magicalbook :public barriers{
private:
    QPixmap img;
public:
    int a[45]={0}, ans[45]={0}, l[2][45], r[2][45],monout[2][45];
    int to[45]={0}, net[45]={0}, w[45]={0},degree[45]={0} ,n, m,sum=0;
    bool hand[45],mis=0;
    int recfutrue[25]={0};
    bool dtl[10]={0};
    QPixmap getimg();
    magicalbook(int x,int y,int width,int height);
    bool jugcollision(int lx,int ly,int wid,int hei);
    void move();
    bool done();
    void spfa();
    void monkrand();
    void monktime();

};
class shrad :public barriers{
private:
    QPixmap img;
public:
    int rec;
    int cnt;
    shrad(int x,int y,int width,int height);
    shradbutton*sbt=NULL;
    QPixmap getimg();
};
class goblin:public barriers{
private:QPixmap img;
public:
    QPixmap getimg();
    goblin(int x,int y,int width,int height);
    void move();
    bool done();
    bool jugcollision(int lx,int ly,int wid,int hei);
    int f[30][30],g[30][30],burger[30],role[30],num;
    void grand(int*bq,int s);
    int steal();
};
class monky:public barriers{
private:
    QPixmap img1;
public:
    monky(int x,int y,int width,int height);
    QPixmap getimg1();

    bool jugcollision(int lx,int ly,int wid,int hei);
    void move();
    bool done();

};
class demo:public barriers{
private:
    QPixmap img;
public:
    QPixmap getimg();
    demo(int x,int y,int width,int height);
    bool jugcollision(int lx,int ly,int wid,int hei);
    void move();
    bool done();

};
class bomb:public barriers{
private:
    QPixmap img;
public:
    QPixmap getimg();
    bomb(int x,int y,int width,int height);
    bool  jugcollision(int lx,int ly,int wid,int hei);
};

#endif // BARRIERS_H
