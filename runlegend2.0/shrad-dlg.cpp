#include"shrad-dlg.h"
#include<QPaintEvent>
#include<QWidget>
#include<QPainter>
#include<QPushButton>
#include<QMessageBox>
#include<QMenu>
#include<QMenuBar>
#define srd ":/new/img/shrand.png"
shradlg::shradlg(QWidget*parent):QDialog(parent){
    bequest*bq=new bequest(40,50,60,70);
    vector<shrad*>s;

    bq->bqrand();
    acc=bq->prize();
    QString accinm=QString::number(acc);
    qDebug()<<acc<<Qt::endl;
        for(int i=0;i<=bq->n;i++){
            int x=20;
            int y=35;
           s.push_back(new shrad(x,y,20,30));
        }


    this->resize(1650,1000);
    this->setWindowTitle("圣者的遗愿");
    int hshrand=450,wshrand=50;
    int k=0;
    l=bq->left;
    r=bq->right;

    QPushButton*ends=new QPushButton(this);
        ends->setStyleSheet("QPushButton{border:5px;}");
        ends->setFixedSize(70,80);
        ends->setParent(this);
        ends->move(1200,150);
        ends->setText("确定");
       qDebug()<<"1";
    for(auto i=s.begin();i!=s.end();i++){
        if(wshrand>1050){
                wshrand=50;
                hshrand-=150;
            }
            rcd[k]=bq->eng[k];
            (*i)->rec=bq->eng[k];
            (*i)->cnt=k;
            (*i)->sbt=new shradbutton(srd,k,bq->eng[k]);
            (*i)->sbt->setParent(this);
            (*i)->sbt->move(wshrand,hshrand);
            wshrand+=100;
             k++;
            connect((*i)->sbt,SIGNAL(clicked()),this,SLOT(shradclk()));
    }
    connect(ends,SIGNAL(clicked()),this,SLOT(shradonclk()));
    connect(ends,SIGNAL(clicked()),this,SLOT(shradrtn()));
     d=k;
     setAttribute (Qt::WA_DeleteOnClose);

    }
void shradlg::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setFont(QFont("黑体",20));
    QPen spen(Qt::black);
    spen.setColor(Qt::black);
    painter.setPen(spen);
    QString inm="亡语:left="+QString::number(l)+","+"right="+QString::number(r);
    painter.drawText(250,600,inm);
    int nhshrad=550,wshrad=50;
    for(int i=1;i<=d;i++){
       if(wshrad>1050) {
           wshrad=50;
           nhshrad-=150;
       }
       painter.drawText(wshrad,nhshrad,QString::number(rcd[i-1]));
       wshrad+=100;
    }


}

shradlg::~shradlg(){
  memset(rcd,0,sizeof(rcd));
}

