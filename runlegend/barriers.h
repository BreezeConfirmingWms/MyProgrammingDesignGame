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
    int eng[155],f[155],que[155],rcd[20],head=1,tail=1;
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
    QPixmap monkimg;
public:
    int a[45], ans[45], l[2][45], r[2][45],monout[2][45], to[45], net[45], w[45],degree[45] ,n, m;
    bool hand[45];
    QPixmap getimg();
    magicalbook(int x,int y,int width,int height);
    bool jugcollision(int lx,int ly,int wid,int hei);
    void move();
    bool done();
    void spfa();
    void monkrand();
    void monktime();
    QLabel*mlabel;

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
    bool done();
};
class goblin:public barriers{
private:QPixmap img;
public:
    QPixmap getimg();
    goblin(int x,int y,int wdth,int height);
    void move();
    bool done();
    bool jugcollision(int lx,int ly,int wid,int hei);
    int f[20][20],g[20][20],burger[20],role[20],num;
    void grand(int*bq,int s);
    int steal();
};

#endif // BARRIERS_H
