#ifndef MYBUTTON_H
#define MYBUTTON_H
#include<QPushButton>
#include<QMouseEvent>
#include<QDebug>
#include<QString>
#include<QSound>

class gameButton:public QPushButton{
    Q_OBJECT
private:
    QPixmap img1;
    QPixmap img2;
public:

    gameButton(QString str,QString cstr);
    ~gameButton(){

    }
    bool isrun;
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mouseReleaseEvent(QMouseEvent*e);
    void init();
signals:

public slots:
};
class shradbutton:public QPushButton{
    Q_OBJECT
private:
     QPixmap img;
public:
    shradbutton(QString str);
    ~shradbutton(){

    }
   void textshrad(int k);

signals:
public slots:
};

#endif // MYBUTTON_H
