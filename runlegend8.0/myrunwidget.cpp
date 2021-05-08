#include"myrunwidget.h"
#include"mybutton.h"
#include"hero.h"

#include<QPainter>
#include<QPaintEvent>
#include<QDebug>
#include<QVector>
#include<queue>
#include<time.h>
#include<QTime>
#include<QMessageBox>
#include<QFile>
#include<QDesktopServices>
#include<QSound>
#define back0 ":/new/img/yhqc.png"
#define back1 ":/new/img/jmsg.png"
#define back2 ":/new/img/qhzz.png"
#define back3 ":/new/img/mfsl.png"
#define back4 ":/new/img/jgsl.png"
#define before ":/new/img/front.png"
#define groundimg ":/new/img/jt.png"
#define hurting ":/new/img/hurt.png"
#define gameover ":/new/img/dpg.png"
#define pause ":/new/img/stopge.png"
#define srad ":/new/img/shrand.png"
#define coinsnd ":/new/img/coin.wav"
#define jumpsnd ":/new/img/jump.wav"
#define oversnd ":/new/img/over.wav"
#define collisionsnd ":/new/img/collision.wav"
#define gblsnd ":/new/img/gbl.wav"
#define mfssnd ":/new/img/mfs.wav"
#define bqsnd ":/new/img/bqst.wav"


using namespace std;
bool gjug=0,magjug=0,mokjug=0,emojug=0,keyjug=1,killjug=1;
int magnum=1;
int keynum=0;
int realnum[10]={0},mcnt=0,cntmp=0;
int pixnum[5]={0,18005,18005,18005,18005};
int sndctrl=0;
gamewidget::gamewidget(QWidget*parent,int wid ,int hei):QWidget(parent){
       QFile file("save.txt");
      QTextStream txtinput(&file);
      QString linestr;
      if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
          return ;
      }
      while(!txtinput.atEnd()){
          linestr=txtinput.readAll();
          maxscore=linestr.toInt();
      }
      file.close();
      this->resize(wid,hei);
      ground_Y=hei-350;
      background[0].load(back0);
      background[1].load(back1);
      background[2].load(back2);
      background[3].load(back3);
      background[4].load(back4);
      initstart.load(before);
      ground.load(groundimg);
      hurtimg.load(hurting);
      pauseimg.load(pause);
      gameoverimg.load(gameover);
      up=down=left=right=false;
      difficult=0;
      isRuning=false;
      isPause=false;
      ground_speed=1;
      ground_X=0;
      Score=0;
      beforegame=true;
      Coinnum=0;
   remove.setInterval(17);
   this->grabKeyboard();
   connect(&remove,&QTimer::timeout,
           [=]()
   {
       r->move(up,down,right,left);
       if(difficult<=80){
           difficult+=0.0015;
       }
       else{
           difficult=80;
       }
       for(auto i=bar1.begin();i!=bar1.end();i++){
           if((*i)->done()){
               bar1.erase(i);
               break;
           }
           else{
               if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid()-5,r->gethei()-5)){
                   QSound::play(collisionsnd);
                   r->reducehp();
              if(r->getscore()>=100)
                  r->setscore(-100);
              else
                  r->setscore(0);
              hurtfbc=255;
              bar1.clear();
              break;
               }
               if(!bar1.empty())
                   (*i)->move();
          }
     }
       for(auto i=bar2.begin();i!=bar2.end();i++){
           if((*i)->done()){
               bar2.erase(i);
               break;
           }
           else{
               if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5)){
                   QSound::play(coinsnd);
                   r->setscore(30);
                   bar2.erase(i);
                   Coinnum++;
                   break;
               }
               if(!bar2.empty())
                   (*i)->move();

           }
       }
       for(auto i=bar3.begin();i!=bar3.end();i++){
           if((*i)->done()){
               bar3.erase(i);
               break;
           }
           else{
               if((*i)->jugcollision(r->getx()-6,r->gety()-6,r->getwid()-6,r->getwid()-6)){
                    QSound::play(collisionsnd);
                   if(r->getscore()>=100)
                       r->setscore(-100);
                   else{
                       r->setscore(0);
                   }
                   r->reducehp();
                   hurtfbc=255;
                   bar3.clear();
                   break;
               }
               if(!bar3.empty())
                   (*i)->move();
           }
       }
       for(auto i=bar4.begin();i!=bar4.end();i++){
           if((*i)->done()){
                   bar4.erase(i);
                   break;
           }
           else{
               if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5)){
                   r->increasehp(700);
                   bar4.clear();
                   break;
               }
               if(!bar4.empty())
                   (*i)->move();
           }
       }
       for(auto i=bar5.begin();i!=bar5.end();i++){
           if((*i)->done()){
               bar5.erase(i);
               break;
           }
           else{
                if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5)){
                    bar5.clear();
                    bar1.clear();
                    bar3.clear();
                    bar6.clear();
                    break;
                }
                if(!bar5.empty())
                        (*i)->move();
           }
       }
        for(auto i=bar6.begin();i!=bar6.end();i++){
                  if((*i)->done())
                   bar6.erase(i);
                   else{
                       if((*i)->jugcollision(r->getx(),r->gety(),r->getwid(),r->getwid())){
                            QSound::play(collisionsnd);
                    if(r->getscore()>=100){
                        r->setscore(-100);
                      }
                   else{
                        r->setscore(0);
                  }
                        r->reducehp();
                        hurtfbc=255;
                        bar6.clear();
                        break;
                 }
                        if(!bar6.empty())
                        (*i)->move();
           }
       }
        for(auto i=bar8.begin();i!=bar8.end();i++){
            if((*i)->done()){
             bar8.erase(i);
             break;
            }
             else{
                 if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5)){

                    if(shradjug){
                      QSound::play(bqsnd);
                     shradlg*sdlg=new shradlg(this);
                     bar3.clear();
                     bar6.clear();
                     r->runtimer.stop();
                     connect(sdlg,SIGNAL(sentdata(int,int,int*,bool)),this,SLOT(recievedata(int ,int ,int*,bool)));
                     isRuning=false;
                     r->hptimer.stop();
                     sdlg->exec();
                     r->setscore(rscore);
                     if(rtn){
                         QString przinm="恭喜你出色地完成了任务，圣光将再次降临你";
                         QMessageBox::about(this,"迸发的能量",przinm);
                         shradlg*sdl=new shradlg(this);
                         connect(sdl,SIGNAL(sentdata(int,int,int*,bool)),this,SLOT(recievedata(int ,int ,int*,bool)));
                         sdl->exec();
                         r->setscore(rscore);
                     }

                     shradjug=0;
                     gjug=1;
                     r->hptimer.start();
                     r->runtimer.start();
                     isRuning=true;
                    }
                    rscore=0;
                    bar8.clear();
                    break;
           }

                 if(!bar8.empty())
                   (*i)->move();

     }
        }
        for(auto i=bar9.begin();i!=bar9.end();i++){
            if((*i)->done()){
                bar9.erase(i);
                break;
            }
            else{
                if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5)){
                     QSound::play(gblsnd);
                  (*i)->grand(roler,tmp);
                    tmp=0;
                    memset(roler,0,sizeof(roler));
                    QString gblinm="作为最精明的怪盗，让我们来博弈吧，我会找到最适合我偷分的方式;\n";
                    gblinm+="你还记得你刚收获的宝物吗？\n";
                    for(int j=1;j<=(*i)->num;j++){
                        if(j==(*i)->num)
                            gblinm+=QString::number((*i)->role[j])+"\n";
                        else
                        gblinm+=QString::number((*i)->role[j])+" ";
                    }
                    gblinm+="这是我的本钱\n";
                    for(int j=1;j<=(*i)->num;j++){
                        if(j==(*i)->num)
                            gblinm+=QString::number((*i)->burger[j])+"\n";
                        else
                        gblinm+=QString::number((*i)->burger[j])+" ";
                    }
                    QMessageBox::about(this,"无语",gblinm);
                    int k=(*i)->steal();
                    r->setscore(-k);
                  bar9.clear();
                  break;
                }
                if(!bar9.empty())
                    (*i)->move();
            }

        }
        for(auto i=bar10.begin();i!=bar10.end();i++){
            if((*i)->done()){
                bar10.erase(i);
                break;
            }
            else{
                if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->gethei()-5,r->gethei()-5)){
                    if(magjug){
                                       QSound::play(mfssnd);
                                       cntmp=0;
                                        mcnt=0;
                                        memset(realnum,0,sizeof(realnum));


                                        if(!(*i)->mis){
                                        QString montxt;
                                        for(int j=1;j<=(*i)->n;j++){
                                            montxt+=QString::number((*i)->l[1][j])+","+QString::number((*i)->r[1][j])+"<<<<<<<<<<<<"+"\n";
                                        }
                                        for(int j=0;j<(*i)->m;j++){
                                            montxt+=QString::number((*i)->monout[0][j])+","+QString::number((*i)->monout[1][j])+"<<<<<<<<<<"+"\n";
                                        }
                                        montxt+="天书的启示:\n";
                                        for(int j=1;j<=(*i)->n;j++){
                                        montxt+=QString::number((*i)->ans[magnum])+"\n";
                                        magnum++;
                                        }
                                        QMessageBox box;
                                        box.setWindowTitle("圣树启示录");
                                        box.setStyleSheet("color:green");
                                        box.resize(850,800);
                                        box.setText(montxt);
                                        box.exec();
                                        if((*i)->sum>=((*i)->n)/2){
                                            emojug=1;
                                            keyjug=1;
                                            srand(time(NULL));
                                            int x=this->width()-500-rand()%300;
                                            int y=60;
                                            for(int j=0;j<10;j++){
                                                if((*i)->dtl[j]){
                                                    realnum[mcnt]=j+((*i)->recfutrue[j])*3+8;
                                                    mcnt++;
                                                }
                                            }
                                            bardemo.push_back(new demo(x,y,150,250));



                                        }
                                        else{
                                            srand(time(NULL));
                                            mokjug=1;
                                            int x=this->width()-450-rand()%250;
                                            int y=40;
                                            barmon.push_back(new monky(x,y,60,80));


                                        }
                                      }
                                        else{
                                            QString warn="泛黄的被遗弃的纸张，好像没有可用信息";
                                            QMessageBox box;
                                            box.about(this,"圣树掉落的魔法书",warn);
                                            box.setStyleSheet("color:yellow");
                                            box.setFixedSize(850,800);
                                        }

                                        magjug=0;
                                        magnum=0;
                    }

                   bar10.clear();
                   break;
                }

                if(!bar10.empty())
                    (*i)->move();
            }
        }

            for(auto j=barmon.begin();j!=barmon.end();j++){
                if((*j)->done()){
                    barmon.erase(j);
                    break;
                }
                else{
                    if((*j)->jugcollision(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5)){
                         QSound::play(collisionsnd);
                        srand(time(NULL));
                        int rcore=150+rand()%180;
                        r->setscore(rcore);
                        r->increasehp(rcore*2-rand()%160);
                        barmon.clear();
                        break;

                    }
                    if(!barmon.empty()){
                        (*j)->move();
                    }
                }
             }
            for(auto j=bardemo.begin();j!=bardemo.end();j++){
                if(keynum==realnum[cntmp]&&killjug&&cntmp<mcnt){
                    keyjug=0;
                if((*j)->done()){
                    cntmp++;
                    keynum=0;
                    keyjug=1;
                    bardemo.erase(j);
                    barbmb.clear();
                    break;
                }
                else{
                    if((*j)->jugcollision(r->getx()-10,r->gety()-10,r->getwid()-25,r->gethei()-15)){
                         QSound::play(collisionsnd);
                        r->reducehp();
                        r->reducehp();
                    }
                    if((*j)->gety()>=this->ground_Y-30){
                        int x=(*j)->getx()-90;
                        int y=this->ground_Y-80;
                        barbmb.push_back(new bomb(x,y,400,200));
                    }
                    if(!bardemo.empty()){
                        (*j)->move();
                    }
                }

              }
            }
            for(auto j=barbmb.begin();j!=barbmb.end();j++){
                if((*j)->jugcollision(r->getx()-10,r->gety()-10,r->getwid()-25,r->gethei()-15)){
                     QSound::play(collisionsnd);
                    r->reducehp();
                    r->setscore(-600);
                    barbmb.clear();
                    break;
                }
            }


       if(isRuning){
           if(r->getcurhpcnt()<=0){
               gameIsOver();
               QFile file("save.txt");
               QTextStream txtinput(&file);
               QString linestr;
               if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
                   qDebug()<<"Open failed."<<Qt::endl;
                   return;
               }
               while(!txtinput.atEnd()){
                   linestr=txtinput.readAll();
                   maxscore=linestr.toInt();
               }
               file.close();
               if(Score>maxscore){
                   if(file.exists()){
                       file.remove();
                   }
                   file.open(QIODevice::WriteOnly);
                   file.close();
                   if(file.open(QFile::WriteOnly|QIODevice::Append|QIODevice::Text)){
                       QTextStream out(&file);
                       out<<Score;
                   }
                   file.close();
               }


           }
           addBarriers();
       }

}
);
}
gamewidget::~gamewidget(){
    delete r;
}

void gamewidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(isRuning==false&&beforegame==true){
        painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(initstart));
    }
    else if(GameOver==true){
        if(GameOver){
            painter.drawPixmap(QRect(240,100,1200,900),gameoverimg);
        }
    }
    else{
        for(int i=0;i<5;i++){
            if(pixnum[i]<=18000){
            painter.drawPixmap(QRect(0,0,this->width(),this->height())
                               ,background[i]
                               ,QRect(backImgX[i],0,this->width(),this->height())
                               );
            if(backImgX[i]>0){
                painter.drawPixmap(QRect(background[i].width()-backImgX[i],0,this->width()-(background[i].width()-backImgX[i]),this->height())
                                   ,background[i]
                                   ,QRect(0,0,this->width()-(background[i].width()-backImgX[i]),this->height())
                                    );
            }
            if(backImgX[i]>=background[i].width()){
                backImgX[i]-=background[i].width();
            }
            if(isRuning&&isPause==false)
            {
                backImgX[i]+=imgSpeed[i];
            }
            if(pixnum[i]==18000&&i<4){
                pixnum[i+1]=0;
            }
            if(pixnum[i]==18000&&i==4){
                pixnum[0]=0;
            }
            pixnum[i]++;
            }

        }
        painter.drawPixmap(QRect(0,ground_Y,this->width(),this->height()-ground_Y)
                           ,ground
                           ,QRect(ground_X,0,this->width(),this->height()-ground_Y)
                           );
        if(ground_X>ground.width()-this->width()){
            painter.drawPixmap(QRect(ground.width()-ground_X,this->ground_Y,this->width()-(ground.width()-ground_X),this->height()-this->ground_Y)
                               ,ground
                               ,QRect(0,0,this->width()-(ground.width()-ground_X),this->height()-this->ground_Y)
                               );
        }
        if(ground_X>=ground.width())
        {
            ground_X-=ground.width();
        }
        if(isRuning&&isPause==false){
            ground_X+=ground_speed;
        }
        painter.drawPixmap(QRect(r->getx(),r->gety(),r->getwid(),r->gethei()),r->getimg());

        if(hurtfbc!=0){
            QPixmap temp(hurtimg.size());
            temp.fill(Qt::transparent);
            QPainter pt(&temp);
            pt.setCompositionMode(QPainter::CompositionMode_Source);
            pt.drawPixmap(0,0,hurtimg);
            pt.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            pt.fillRect(temp.rect(),QColor(0,0,0,hurtfbc));
            painter.drawPixmap(QRect(0,0,this->width(),this->height()),temp);
            hurtfbc-=3;
        }
        painter.drawRect(QRect(1000,50,150,10));
        painter.fillRect(QRect(1000,50,r->getcurhpcnt()*150/100,10),Qt::red);
        painter.drawLine(1050,50,1050,60);
        painter.drawLine(1100,50,1100,60);
        QPen pen1(Qt::yellow);
        painter.setFont(QFont("黑体",20));
        pen1.setColor(Qt::yellow);
        painter.setPen(pen1);
        painter.drawText(1000,100,QString("HP:%1%").arg(r->getcurhpcnt()));
        painter.drawText(100,100,QString("Coinnum:%1%").arg(Coinnum));
        painter.drawText(500,100,QString("Score:%1%").arg(r->getscore()));

        for(auto i=bar1.begin();i!=bar1.end();i++){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());
        }
        for(auto i=bar2.begin();i!=bar2.end();i++){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());

        }
        for(auto i=bar3.begin();i!=bar3.end();i++){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());
        }
        for(auto i=bar4.begin();i!=bar4.end();i++){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());
        }
        for(auto i=bar5.begin();i!=bar5.end();i++){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());
        }
        for(auto i=bar6.begin();i!=bar6.end();i++){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());
        }
        for(auto i=bar8.begin();i!=bar8.end();i++){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());
        }
        for(auto i=bar9.begin();i!=bar9.end();i++){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());
        }
        for(auto i=bar10.begin();i!=bar10.end();i++){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());
        }
        for(auto i=barmon.begin();i!=barmon.end();i++){

                painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg1());
        }
        for(auto i=bardemo.begin();i!=bardemo.end();i++){
            if(keynum==realnum[cntmp]){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());
            }
        }
        for(auto i=barbmb.begin();i!=barbmb.end();i++){
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwidth(),(*i)->getheight()),(*i)->getimg());
        }
        if(isPause&&!GameOver){
            painter.drawPixmap((this->width()-pauseimg.width())/2,(this->height()-pauseimg.height())/2,pauseimg);
        }
         update();
    }
}
void gamewidget::recievedata(int a,int b,int*d,bool c){
    rscore=a;
    tmp=b;
    roler=d;
    rtn=c;
}
void gamewidget::addBarriers()
{
    static int Lastwall_time;
    srand(time(NULL));
    if(Lastwall_time>=200-difficult)
    {
        int x=this->width()+10;
        int y=this->ground_Y-100-(rand()%(int)(ground_Y*0.4));
        bar1.push_back(new Wall(x,y,70,ground_Y-y));
        Lastwall_time=0;
    }
    Lastwall_time++;
    static int Lastcoin_time;
    if(Lastcoin_time>=30-difficult)
    {
        int x=this->width()+5;
        int y=ground_Y-45-rand()%300;
        bar2.push_back(new coin(x,y,30,40));
        Lastcoin_time=0;

    }
    Lastcoin_time++;

    static int Lastarrow_time;
    if(Lastarrow_time>=100-difficult)
    {
        int x=this->width()+100;
        int y=ground_Y-50-rand()%400;
        bar3.push_back(new arrow(x,y,300,80));
        Lastarrow_time=0;
    }
    Lastarrow_time++;
    static int Lastblood_time;
    if(Lastblood_time>=550-difficult/2)
    {
        int x=this->width()+10;
        int y=ground_Y-45-rand()%300;
        bar4.push_back(new mbottle(x,y,40,60));
        Lastblood_time=0;
    }
    Lastblood_time++;
    static int LastAscepter_time;
    if(LastAscepter_time>=750+difficult){
        int x=this->width()+10;
        int y=ground_Y-55-rand()%300;
        bar5.push_back(new Ascepter(x,y,50,70));
        LastAscepter_time=0;
    }
    LastAscepter_time++;
    static int Lastcircle_time;
    if(Lastcircle_time>=190-difficult)
    {
        int x=this->width()+100;
        int y=ground_Y-90-rand()%400;
        bar6.push_back(new circle(x,y,90,100));
        Lastcircle_time=0;
    }
    Lastcircle_time++;
    static int Lastbequest_time;
    if(Lastbequest_time>=1350){
        int x=this->width()+10;
        int y=ground_Y-75-rand()%250;
        bar8.push_back(new bequest(x,y,80,100));
        shradjug=1;
        Lastbequest_time=0;
    }
    Lastbequest_time++;
    static int Lastgbl_time;
     if(Lastgbl_time>=385){
         if(gjug){
            int x=this->width()+10;
            int y=ground_Y-60-rand()%125;
             bar9.push_back(new goblin(x,y,100,120));
             gjug=0;
         }
             Lastgbl_time=0;
        }
        Lastgbl_time++;
    static int Lastmagbook_time;
     if(Lastmagbook_time>=2250){
                int x=this->width()+10;
                int y=this->ground_Y-100-rand()%125;
                bar10.push_back(new magicalbook(x,y,90,100));
                int mx=this->width()+250+rand()%400;
                int my=this->height()+20;
                barmon.push_back(new monky(mx,my,100,120));
                for(auto i=bar10.begin();i!=bar10.end();i++){
                     (*i)->monkrand();
                    (*i)->monktime();
                }
                magjug=1;
                Lastmagbook_time=0;
            }
            Lastmagbook_time++;


}

void gamewidget::start_game()
{
    r= new hero(this);
    r->runtimer.start();
    remove.start();
    r->hptimer.start();
    GameOver=false;
    beforegame=false;
    isRuning=true;
    Coinnum=0;
    isPause=false;
    update();

}
void gamewidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        if(sndctrl==3){
            QSound::play(jumpsnd);
            sndctrl=0;
        }
        else{
            sndctrl++;
        }
        up=true;
        if(emojug&&keyjug){
        keynum++;
        }

    }
    else if(event->key()==Qt::Key_S)
    {
        down=true;
        if(emojug&&keyjug){
        keynum++;
        }
    }
    else if(event->key()==Qt::Key_D)
    {
        right=true;
        if(emojug&&keyjug){
        keynum++;
        }
    }
    else if(event->key()==Qt::Key_A)
    {
        left =true;
        if(emojug&&keyjug){
        keynum++;
        }
    }
    else if(!GameOver&&event->key()==Qt::Key_Escape)
    {
        if(isPause==false)
        {
            r->hptimer.stop();
            gamepause();
        }
        else
        {
            r->hptimer.start();
            gamecontinue();
        }
    }
    else if(!GameOver&&isRuning&&!isPause&&event->key()==Qt::Key_Q)
    {
        r->dashmove();
        if(emojug&&keyjug){
        keynum++;
        }

    }
    else if(isRuning&&event->key()==Qt::Key_K){
        if(keynum==realnum[cntmp]&&realnum[cntmp]!=0){
            keynum=0;
            keyjug=0;
            killjug=0;
            bardemo.clear();
        }
        else
            if(emojug&&keyjug){
                keynum++;
            }
    }
    else if(GameOver&&event->key()==Qt::Key_R)
    {
        bar1.clear();
        bar2.clear();
        bar3.clear();
        bar4.clear();
        bar8.clear();
        bar9.clear();
        bar10.clear();
        bardemo.clear();
        barmon.clear();
        barbmb.clear();

        start_game();
    }
    else if(GameOver&&event->key()==Qt::Key_B)
    {
        back();
    }
    else
    {
        return QWidget::keyPressEvent(event);
    }
}
void gamewidget::back()
{
    QFile file("save.txt");
    QTextStream txtinput(&file);
    QString linestr;
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Open failed."<<Qt::endl;
        return;
    }
    while(!txtinput.atEnd())
    {
       linestr=txtinput.readAll();
        maxscore=linestr.toInt();
    }
      file.close();

            beforegame=true;
            but1->move(1000,400);
            but1->show();
            but2->show();
            but3->show();
            but4->show();
            update();
}
void gamewidget::gamepause()
{
      isPause=true;
            remove.stop();
            r->pausehero();
}
void gamewidget::gamecontinue(){
    isPause=false;
    remove.start();
    r->continuehero();
}
void gamewidget::keyReleaseEvent(QKeyEvent *event)
    {
            if(event->key()==Qt::Key_W)
           {
                up=false;
            }
            else if(event->key()==Qt::Key_S)
            {
                down=false;
            }
            else if(event->key()==Qt::Key_D)
            {
                right=false;
            }
            else if(event->key()==Qt::Key_A)
            {
                left =false;
            }
            else
           {
            return QWidget::keyPressEvent(event);
           }
}
void gamewidget::gameIsOver()
{

    QSound::play(oversnd);
    Score=r->getscore();
    if(Score>maxscore)
    {
        maxscore=Score;
    }
    r->hptimer.stop();
    QString str="你的分数:"+QString("%1").arg(r->getscore())+"\n"+"你的金币:"+QString("%1").arg(Coinnum);
    QMessageBox::about(this,"游戏结束",str);
    QFile file("save.txt");
    QTextStream txtinput(&file);
    QString linestr;
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Open failed."<<Qt::endl;
        return ;
    }
    while(!txtinput.atEnd())
    {
        linestr=txtinput.readAll();
        maxscore=linestr.toInt();


    }
    file.close();

    isRuning=false;
    GameOver=true;

    remove.stop();
    bar1.clear();
    bar2.clear();
    bar3.clear();
    bar4.clear();
    bar8.clear();
    bar9.clear();
    bar10.clear();
    bardemo.clear();
    barmon.clear();
    barbmb.clear();

    r->runtimer.stop();
    delete r;
    update();
}
