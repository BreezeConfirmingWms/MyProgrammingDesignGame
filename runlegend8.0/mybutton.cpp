#include"mybutton.h"
#include<QPushButton>
#include<QPainter>
#include<QSound>

#define btnsnd ":/new/img/button.wav"

gameButton::gameButton(QString str,QString cstr){
  img1.load(str);
  img2.load(cstr);
  this->setStyleSheet("QPushButton{border:0px;}");
  this->setFixedSize(QSize(img1.width(),img1.height()));
  this->setIcon(img1);
  this->setIconSize(QSize(img1.width(),img1.height()));
  isrun=false;
}
void gameButton::init(){
    this->move(600,400);
}
void gameButton::mouseReleaseEvent(QMouseEvent *e){

    QSound::play(btnsnd);
    return QPushButton::mouseReleaseEvent(e);
}
void gameButton::enterEvent(QEvent*){

    this->setFixedSize(QSize(img2.width(),img2.height()));
    this->setIcon(img2);
    this->setIconSize(QSize(img2.width(),img2.height()));
    this->move(this->x()-50,this->y()-50);
}
void gameButton::leaveEvent(QEvent *){

    this->setFixedSize(QSize(img1.width(),img1.height()));
    this->setIcon(img1);
    this->setIconSize(QSize(img1.width(),img1.height()));
    this->move(this->x()+50,this->y()+50);
}
shradbutton::shradbutton(QString str,int r,int p){
    rec=r;
    pos=p;
    img.load(str);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setFixedSize(QSize(img.width(),img.height()));
    this->setIcon(img);
    this->setIconSize(QSize(img.width(),img.height()));
}
int shradbutton::rtnrec(){
    return this->rec;
}
int shradbutton::rtnpos(){
    return this->pos;
}
