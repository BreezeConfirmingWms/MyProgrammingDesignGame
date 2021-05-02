#ifndef SHRADDLG_H
#define SHRADDLG_H
#include<QDialog>
#include<QVector>
#include<vector>
#include"barriers.h"
using namespace std;

class shradlg :public QDialog{
    Q_OBJECT
private:
public:
    shradlg( vector<shrad*>s,int left,int right,int*eng);
    ~shradlg();
    int roler[30];
    int cnt=0,tmp=0,rscore=0;

 };
#endif // SHRADDLG_H
