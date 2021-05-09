#include<barriers.h>
#include<QTimer>
#include<QDebug>
#include<ctime>
#include<QTime>
#include<queue>
#include<algorithm>
#include<cstring>


#define Wall_1 ":/new/img/wall-1.png"
#define Wall_2 ":/new/img/wall-2.png "
#define Wall_3 ":/new/img/wall-3.png"
#define coin_1 ":/new/img/coin_001.png"
#define coin_2 ":/new/img/coin_002.png"
#define coin_3 ":/new/img/coin_003.png"
#define coin_4 ":/new/img/coin_004.png"
#define arrow_1 ":/new/img/arrow1.png"
#define blood ":/new/img/mbottle.png"
#define ascepter ":/new/img/ascepter.png"
#define circle1 ":/new/img/ncircle.png"
#define pbequest ":/new/img/bequest.png"
#define pshrand ":/new/img/shrand.png"
#define magbook ":/new/img/magicalbook.png"
#define gbl ":/new/img/gbl.png"
#define mky ":/new/img/monkey.png"
#define emo ":/new/img/emo.png"
#define bmb ":/new/img/bomb.png"

barriers::barriers(int x,int y,int width,int height){
    this->x=x;
    this->y=y;
    this->width=width;
    this->height=height;
}
int barriers::getx(){
    return this->x;
}
int barriers::gety(){
    return this->y;
}
void barriers::setx(int x)
{
    this->x=x;
}
void barriers::sety(int y)
{
    this->y=y;
}
int barriers::getwidth(){
    return this->width;
}
int barriers::getheight(){
    return this->height;
}
Wall::Wall(int x, int y, int width, int height)
    :barriers(x,y,width,height)
{
 srand(time(NULL));
this->img.load(QString(":/new/img/wall-%1.png").arg(rand()%3+1));//三种墙体随机取出
}
bool Wall::jugcollision(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwidth(),this->getheight());
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
QPixmap Wall::getimg()
{
    return this->img;
}
void Wall::move(){
    this->setx(this->getx()-5);//实时更新坐标达到运动效果
}
bool Wall::done(){
   if(this->getx()<=-(this->getwidth()))//判断物体是否移出界面
      return true;
   else
       return false;
}
coin::coin(int x,int y,int width,int height)
    :barriers(x,y,width,height){
    this->img[0].load(QString(":/new/img/coin_001.png"));
    this->img[1].load(QString(":/new/img/coin_002.png"));
    this->img[2].load(QString(":/new/img/coin_003.png"));
    this->img[3].load(QString(":/new/img/coin_004.png"));
    cointime=0;
    coinout.setInterval(100);
    QObject::connect(&coinout,&QTimer::timeout,
               [=]()
               {
                   cointime=(cointime+1)%3;// 通过定时器加载一组图片实现金币翻转效果
               }
         );
    coinout.start();
}
QPixmap coin::getimg(){
    return this->img[cointime];
}
bool coin::jugcollision(int lx,int ly,int wid,int hei){
    QRect rect_1(this->getx(),this->gety(),this->getwidth()-30,this->getheight()+20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
void coin::move(){
    this->setx(this->getx()-5);
}
bool coin::done(){
    if(this->getx()<-10)
        return true;
    else
        return false;
}
mbottle::mbottle(int x,int y,int width,int height)
    :barriers(x,y,width,height){
    img.load(blood);
}
QPixmap mbottle::getimg(){
    return this->img;
}
bool mbottle::jugcollision(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwidth()-30,this->getheight()+20);//碰撞检测函数，主要为了方便向主窗口传参，下同。
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
void mbottle::move(){
    this->setx(this->getx()-5);
}
bool mbottle::done(){
    if(this->getx()<-10)
        return true;
    else
        return false;
}
Ascepter::Ascepter(int x,int y,int width,int height)
    :barriers(x,y,width,height){
    img.load(ascepter);
}
QPixmap Ascepter::getimg(){
    return this->img;
}
bool Ascepter::jugcollision(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwidth()-30,this->getheight()+20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
void Ascepter::move(){
    this->setx(this->getx()-5);
}
bool Ascepter::done(){
    if(this->getx()<-10)
        return true;
    else
        return false;
}

arrow::arrow(int x,int y,int width,int height)
    :barriers(x,y,width,height){
    img.load(arrow_1);
}
QPixmap arrow::getimg(){
    return this->img;
}
bool arrow::jugcollision(int lx,int ly,int wid,int hei){
    QRect rect_1(this->getx(),this->gety(),this->getwidth()-250,this->getheight()-20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
void  arrow::move(){
    this->setx(getx()-10);
}
bool arrow::done(){
    if(this->getx()<=(-this->getwidth()))
        return true;
    else
        return false;
}
circle::circle(int x,int y,int width,int height)
    :barriers(x,y,width,height){
    img.load(circle1);
    img.scaled(width,width);
    this->r=width/2;//半径
    this->collisionqwidth=width*0.7;//弧度制
    this->collisionangle=width*0.15;//弧度制
}
QPixmap circle::getimg(){
    QTransform  m;
    degree+=1;
    if(degree>=360)
        degree=0;
    m.rotate(degree);//旋转与切换
    return this->img.transformed(m,Qt::FastTransformation);
}
bool circle::jugcollision(int px,int py,int pwid,int phei){
    QRect rect_1(this->getx()+collisionangle,this->gety()+collisionangle,collisionqwidth,collisionqwidth);
    QRect rect_2(px,py,pwid,phei);
    return rect_1.intersects(rect_2);
}
void circle::move(){
    this->setx(this->getx()-7);
}
bool circle::done(){
    if(this->getx()<=-this->getwidth())
        return true;
    else
        return false;
}
bequest::bequest(int x,int y,int width,int height)
    :barriers(x,y,width,height)
{
    img.load(pbequest);
   }
QPixmap bequest::getimg(){
    return this->img;
}
void bequest::move(){
    this->setx(this->getx()-6);
}
bool bequest::done(){
    if(this->getx()<-10)
        return true;
    else
        return false;
}
bool bequest::jugcollision(int lx, int ly, int wid, int hei){
    QRect rect_1(this->getx(),this->gety(),this->getwidth()-30,this->getheight()+20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
void bequest::bqrand(){
    srand(time(NULL));
    n=rand()%6+30;
    left=rand()%2+3;
    right=rand()%3+5;
    int i=1;
    eng[0]=0;
    while(i<=n){
        eng[i]=rand()%53+10;
        i++;
    }
}
int bequest::quefind(int x){
    while (que[head] + right< x)
            head++;
      return que[head];
}
int bequest::prize(){
    int ans=-5;
    memset(que,0,sizeof(que));
    memset(f, 128, sizeof(f));
    f[0]=0;
    for (int i = left; i <= n; i++) {
        while( f[i-left] >= f[que[tail]] && tail >= head)
                tail--;
            que[++tail] = i-left;
            int from = quefind(i);
            f[i] = f[from] + eng[i];
            if (i + right> n){
               ans=std::max(ans,f[i]);//返回固定移动范围内走法最大权
            }
        }
return ans;
}
goblin::goblin(int x,int y,int width,int height)
    :barriers( x, y, width, height)
{
    img.load(gbl);
}
QPixmap goblin::getimg(){
    return this->img;
}
void goblin::move(){
    this->setx(this->getx()-12);
}
bool goblin::done(){
    if(this->getx()<-10)
        return true;
    else
        return false;
}
void goblin::grand(int*bq,int s){
    srand(time(NULL));
    num=s-1;
    for(int i=1;i<=num;i++){
        role[i]=bq[i];
        burger[i]=role[i]+rand()%30-12;
    }
}//随机数据保证数据正态分布
bool cmp(int a, int b){
      return a>b;
}
int goblin::steal(){
    std::sort( role, role + num,cmp);
    std::sort(burger ,burger + num,cmp);
    memset(g, 0, sizeof(g));
    for (int i = 1; i <=num; i++) {
            for (int j = 1; j <= num; j++) {
                if (role[i] >burger[j])
                    g[i][j] = -100;
                if (role[i] < burger[j])
                    g[i][j] = +150;
            }
        }
    memset(f, -0x7f, sizeof(f));
        f[0][0] = 0;
        for (int i = 1; i <= num; i++) {
            f[i][0] = f[i - 1][0] + g[num - i + 1][i];
            f[i][i] = f[i - 1][i - 1] + g[i][i];
            for (int j = 0; j < i; j++)
                f[i][j] = std::max(f[i - 1][j] + g[num - (i - j) + 1][i], f[i - 1][j - 1] + g[j][i]);
        }
        int ans=f[num][0];
        for (int i = 2; i <= num; i++) {
            ans = std::max(ans, f[num][i]);
        }
        return ans;
}//计算最大损失
bool goblin::jugcollision(int lx, int ly, int wid, int hei){
    QRect rect_1(this->getx(),this->gety(),this->getwidth()-30,this->getheight()+20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
shrad::shrad(int x,int y,int width,int height)
    :barriers(x,y,width,height){
    img.load(pshrand);
}
QPixmap shrad::getimg(){
    return this->img;
}
magicalbook::magicalbook(int x,int y,int width,int height)
    :barriers(x,y,width,height){
         img.load(magbook);

         }
bool magicalbook::jugcollision(int lx, int ly, int wid, int hei){
    QRect rect_1(this->getx(),this->gety(),this->getwidth()-30,this->getheight()+20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
QPixmap magicalbook::getimg(){
    return this->img;
}
monky::monky(int x,int y,int width,int height)
    :barriers(x,y,width,height){
    img1.load(mky);
}
QPixmap monky::getimg1(){
    return this->img1;
}

void magicalbook::move(){
    this->setx(this->getx()-4);
}
void monky::move(){
    this->sety(this->gety()+15);
}

bool monky::done(){
    if(this->gety()>750)
        return true;
    else
        return false;
}
bool monky::jugcollision(int lx, int ly, int wid, int hei){
    QRect rect_1(this->getx(),this->gety(),this->getwidth()-40,this->getheight()+30);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
demo::demo(int x,int y,int width,int height)
    :barriers(x,y,width,height){
    img.load(emo);
}
void demo::move(){
    this->sety(this->gety()+20);
}
bool demo::done(){
    if(this->gety()>1200)
        return true;
    else
        return false;
}
QPixmap demo::getimg(){
    return this->img;
}
bool demo::jugcollision(int lx, int ly, int wid, int hei){
    QRect rect_1(this->getx(),this->gety(),this->getwidth()-40,this->getheight()+30);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
bool magicalbook::done(){
    if(this->getx()<-10)
        return true;
    else
        return false;
}
void magicalbook::monkrand(){
    srand(time(NULL));
     n=rand()%8+8;
     m=6+rand()%2-3;
     memset(hand,0,sizeof(hand));
     int k=4;
     for(int i=1;i<=n;i++){
         int cur=i;
         if(cur<=3){
         l[1][i]=cur+rand()%2+1;
         r[1][i]=cur+rand()%2+1;
         }
         else{
            int ljug=(rand()*rand())%2;
            int rjug=(rand()*13)%2;
            if(ljug==1){
                l[1][i]=cur+1;
            }
            else{
                l[1][i]=cur-1;
            }
            if(rjug==1){
                if(cur+1==l[1][i])
                    r[1][i]=cur+2;
                else
                    r[1][i]=cur+1;
            }
            else{
                if(cur-1==l[1][i]){
                  r[1][i]=cur-2;
                }
                else
                    r[1][i]=cur-1;            }
         }
         l[0][i]=m;
         r[0][i]=m;

     }
     while(k>2){
         int s=rand()%n+1;
         if(!hand[s]){
         l[1][s]=-1;
         hand[s]=true;
         k--;
         }
     }
     while(k>0){
         int s=rand()%n+1;
         if(!hand[s]){
         r[1][s]=-1;
         hand[s]=true;
         k--;
         }
     }
     memset(hand,0,sizeof(hand));
}//随机造数据，先连边再加权。
void magicalbook::spfa(){
    std::queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = a[u]; i; i = net[i]) {
                int v = to[i], wd = std::min(ans[u], w[i]);
                if (wd > ans[v]) {
                    ans[v] = wd;
                    q.push(v);
                }

            }
        }
}
void magicalbook::monktime(){
    ans[1]=m;
    for (int i = 0; i < m; i++) {
           int x=rand()%n+1;
           int y=rand()%2+1;
           monout[0][i]=x;
           monout[1][i]=y;
            if (y == 1)
                l[0][x] = std::min(i, l[0][x]);
            if (y == 2)
                r[0][x] = std::min(i, r[0][x]);
        }
    int t = 0;
        for (int i = 1; i <= n; i++) {
            int x = l[1][i], y = r[1][i];
            if (x != -1) {
                net[++t] = a[i], to[t] = x, w[t] = l[0][i], a[i] = t;
                net[++t] = a[x], to[t] = i, w[t] = l[0][i], a[x] = t;
            }
            if (y != -1) {
                net[++t] = a[i], to[t] = y, w[t] = r[0][i], a[i] = t;
                net[++t] = a[y], to[t] = i, w[t] = r[0][i], a[y] = t;
            }
        }
        spfa();
        if(mis){
            return;
        }
        for(int i=1;i<=n;i++){
            if(ans[i]==m)
                ans[i]=-1;
        }
        for(int i=1;i<=n;i++){
            if(ans[i]>=0){
                recfutrue[ans[i]]++;
                sum++;
            }
        }
        for(int i=0;i<10;i++){
            if(recfutrue[i]>0){
                dtl[i]=1;
            }
        }
}
bomb::bomb(int x,int y,int width,int height)
    :barriers(x,y,width,height){
    img.load(bmb);
}
QPixmap bomb::getimg(){
    return this->img;
}
bool bomb::jugcollision(int lx, int ly, int wid, int hei){
    QRect rect_1(this->getx(),this->gety(),this->getwidth()-30,this->getheight()+15);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);
}
