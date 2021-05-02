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


using namespace std;
int rscore=0;
int cnt=0,tmp=0;
bool rtn=0,jug=0;;
int roler[20],fbk=0;
int magnum=1;
bool shradjug=0,clearjug=0;
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
      ground_Y=hei-250;
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
   remove.setInterval(15);
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
               i=bar1.erase(i);
           }
           else{
               if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid(),r->gethei()-5)){
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
               i=bar2.erase(i);
           }
           else{
               if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid()-5,r->gethei()-5)){
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
           if((*i)->done())
               i=bar3.erase(i);
           else{
               if((*i)->jugcollision(r->getx(),r->gety(),r->getwid(),r->gethei())){
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
                   i=bar4.erase(i);
           }
           else{
               if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid(),r->getwid()-5)){
                   r->increasehp(700);
                   i=bar4.erase(i);
                   break;
               }
               if(!bar4.empty())
                   (*i)->move();
           }
       }
       for(auto i=bar5.begin();i!=bar5.end();i++){
           if((*i)->done())
               i=bar5.erase(i);
           else{
                if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid(),r->getwid()-5)){
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
                   i=bar6.erase(i);
                   else{
                       if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid(),r->gethei()-5)){
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
            if((*i)->done())
             i=bar8.erase(i);
             else{
                 jug=0;
                 if((*i)->jugcollision(r->getx()-5,r->gety()-5,r->getwid(),r->gethei()-5)){
                   addshrad(*i);
                   (*i)->num=tmp;
                                    for(int j=0;j<tmp;j++){
                                        (*i)->rcd[j]=roler[j];
                                    }
                                    fbk=(*i)->num;
                                    for(auto i=bar7.begin();i!=bar7.end();i++){
                                        delete (*i)->sbt;
                                    }
                                    bar7.clear();
                                    if(rscore==(*i)->prize()&&!jug){
                                        tmp=0;
                                        jug=1;
                                        (*i)->bqrand();
                                        addshrad(*i);
                                        (*i)->num=tmp;
                                        for(int j=0;j<tmp;j++){
                                            (*i)->rcd[j]=roler[j];
                                        }
                                        fbk=(*i)->num;
                                        for(auto i=bar7.begin();i!=bar7.end();i++){
                                            delete (*i)->sbt;
                                        }
                                    }
                                    r->setscore(rscore);
                                    rscore=0;

           }
                  if(!bar8.empty())
                  (*i)->move();
     }
        }
        for(auto i=bar9.begin();i!=bar9.end();i++){
            if((*i)->done()){
                i=bar9.erase(i);
            }
            else{
                if((*i)->jugcollision(r->getx()-6,r->gety()-6,r->getwid(),r->gethei()-8)){
                  (*i)->grand(roler,fbk);
                    int f=(*i)->steal();
                    r->setscore(-f);
                }
            }
            if(!bar9.empty())
                (*i)->move();
        }
        for(auto i=bar10.begin();i!=bar10.end();i++){
            if((*i)->done()){
                i=bar10.erase(i);
            }
            else{
                if((*i)->jugcollision(r->getx()-7,r->gety()-7,r->getwid(),r->gethei()-9)){
                   (*i)->monkrand();
                    QString montxt="";
                    for(int j=1;j<=(*i)->n;j++){
                        montxt+=QString::number((*i)->l[1][j])+","+QString::number((*i)->r[1][j])+"\n";
                    }
                    for(int j=0;j<(*i)->m;j++){
                        montxt+=QString::number((*i)->monout[0][j])+","+QString::number((*i)->monout[1][j])+"\n";
                    }
                    montxt+="天书的启示:"+QString::number((*i)->ans[magnum]);
                    magnum++;
                    QMessageBox::about(this,"圣树掉落的魔法书,奇怪的能量……",montxt);
                }
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
            painter.drawPixmap(QRect(240,60,800,600),gameoverimg);
        }
    }
    else{
        for(int i=0;i<5;i++){
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
        QPen pen1(Qt::black);
        painter.setFont(QFont("黑体",20));
        pen1.setColor(Qt::black);
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
        if(isPause&&!GameOver){
            painter.drawPixmap((this->width()-pauseimg.width())/2,(this->height()-pauseimg.height())/2,pauseimg);
        }
         update();
    }
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
        int y=ground_Y-80-rand()%300;
        bar2.push_back(new coin(x,y,30,40));
        Lastcoin_time=0;

    }
    Lastcoin_time++;

    static int Lastarrow_time;
    if(Lastarrow_time>=100-difficult)
    {
        int x=this->width()+100;
        int y=ground_Y-80-rand()%400;
        bar3.push_back(new arrow(x,y,300,100));
        Lastarrow_time=0;
    }
    Lastarrow_time++;
    static int Lastblood_time;
    if(Lastblood_time>=250)
    {
        int x=this->width()+10;
        int y=ground_Y-45-rand()%300;
        bar4.push_back(new mbottle(x,y,40,40));
        Lastblood_time=0;
    }
    Lastblood_time++;
    static int LastAscepter_time;
    if(LastAscepter_time>=250){
        int x=this->width()+10;
        int y=ground_Y-55-rand()%300;
        bar5.push_back(new Ascepter(x,y,40,70));
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
    if(Lastbequest_time>=430){
        int x=this->width()+10;
        int y=ground_Y-75-rand()%100;
        bar8.push_back(new bequest(x,y,50,70));
        for(auto i=bar8.begin();i!=bar8.end();i++){
            (*i)->bqrand();
        }
        Lastbequest_time=0;
    }
    Lastbequest_time++;
    static int Lastgbl_time;
    if(Lastgbl_time>=300){
        if(rtn){
        int x=this->width()+15;
        int y=ground_Y-60-rand()%125;
        bar9.push_back(new goblin(x,y,100,150));
        }
        Lastgbl_time=0;
    }
    Lastgbl_time++;
    static int Lastmagbook_time;
    if(Lastmagbook_time>=600){
        int x=this->width()+10;
        int y=this->ground_Y-70-rand()%130;
        bar10.push_back(new magicalbook(x,y,80,100));
        Lastmagbook_time=0;
    }
    Lastmagbook_time++;
}
void gamewidget::addshrad(bequest(*bq)){
    int dist=5;
    for(int i=0;i<bq->n;i++){
        int x=this->width()+dist;
        int y=this->ground_Y-75;
        bar7.push_back(new shrad(x,y,20,30));
    }
    QString inm="left="+QString::number(bq->left)+","+"right="+QString::number(bq->right);
    QMessageBox::about(this,"亡语",inm);
    shradlg sdlg(bar7,bq->left,bq->right,bq->eng);
    sdlg.setModal(true);
    sdlg.exec();
    if(cnt+bq->left>bq->n){
       cnt=sdlg.cnt;
       tmp=sdlg.cnt;
       rscore=sdlg.cnt;
    }
    cnt=sdlg.cnt;
    tmp=sdlg.cnt;
    rscore=sdlg.cnt;
    for(int i=0;i<tmp;i++){
        roler[i]=sdlg.roler[i];
    }

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
        up=true;


    }
    else if(event->key()==Qt::Key_S)
    {
        down=true;
    }
    else if(event->key()==Qt::Key_D)
    {
        right=true;
    }
    else if(event->key()==Qt::Key_A)
    {
        left =true;
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

    }
    else if(GameOver&&event->key()==Qt::Key_R)
    {
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
            but1->move(900,400);
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

    r->runtimer.stop();
    r->hptimer.stop();
    delete r;
    update();
}
