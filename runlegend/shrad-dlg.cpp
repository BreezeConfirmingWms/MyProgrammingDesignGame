#include"shrad-dlg.h"
#include<QPaintEvent>
#include<QPainter>
#include<QPushButton>
#include<QMessageBox>
#include<QMenu>
#include<QMenuBar>
#define srd ":/new/img/shrand.png"
shradlg::shradlg(vector<shrad*>s,int left,int right,int*eng){
    this->resize(1650,1000);
    int hshrand=450,wshrand=50;
    for(auto i=s.begin();i!=s.end();i++){
        int k=0;
        if(wshrand>1050){
                wshrand=50;
                hshrand-=150;
            }
            (*i)->rec=eng[k];
            (*i)->cnt=k;
            (*i)->sbt=new shradbutton(srd);
            (*i)->sbt->textshrad(eng[k]);
            (*i)->sbt->setParent(this);
            (*i)->sbt->move(wshrand,hshrand);
            wshrand+=100;
            connect((*i)->sbt,&QPushButton::clicked,this,
                            [=]{
                        if((*i)->cnt>=cnt+left&&(*i)->cnt<=cnt+right){
                            cnt=(*i)->cnt;
                            rscore+=eng[cnt];
                            roler[tmp]=eng[cnt];
                            tmp++;
                            (*i)->sbt->hide();
                        }
                    }
            );

            k++;
    }

}
shradlg::~shradlg(){
   qDebug()<<"666";
}
