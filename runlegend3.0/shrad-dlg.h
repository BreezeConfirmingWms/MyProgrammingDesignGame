#ifndef SHRADDLG_H
#define SHRADDLG_H
#include<QDialog>
#include<QVector>
#include<vector>
#include<QMessageBox>
#include<QPaintEvent>
#include"barriers.h"
#include"mybutton.h"
using namespace std;

class shradlg :public QDialog{
    Q_OBJECT
public:
    explicit shradlg(QWidget*parent=nullptr);
    ~shradlg();
    void paintEvent(QPaintEvent*);
    int *roler=new int[50];
    int cnt=0,tmp=1,rscore=0;
    int rcd[30];
    int d=0;
    int l=0,r=0;
    bool jug=0;
    int acc=0;
signals:
     void sentdata(int,int,int*,bool);
public slots:
    void shradclk(){
        shradbutton*sr=(shradbutton*)sender();
        int k=sr->rtnrec();
        int scr=sr->rtnpos();
        if(k<=cnt+r&&k>=cnt+l){
            cnt=k;
            rscore+=scr;
            roler[tmp]=scr;
            tmp++;
            sr->hide();
            if(rscore==acc){
                jug=1;
            }
        }
        else{
            QString errs="看来圣者任务的进程有小波折，勇士再续征程吧!";
            QMessageBox::about(this,"再接再厉",errs);
        }
    };
    void shradrtn(){
        if(cnt+l>d-1){
       accept();
        }
    }
    void shradonclk(){
        if(cnt+l>d-1){
        emit sentdata(rscore,tmp,roler,jug);
        }
    }

 };
#endif // SHRADDLG_H
