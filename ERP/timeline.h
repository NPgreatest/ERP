#ifndef TIMELINE_H
#define TIMELINE_H
#include<QVector>
#include"store.h"
#include"request.h"
#include"part_check.h"



class timeline
{
private:
    part_check checker;
    store store;
    QVector<request> requests;


    void DFS_sort();
    void Sort_By_Date();
    void Calculate_Time();
    void Calculate_Store();
public:
    timeline();
    void Insert_Part(QString part_no,QString name,QString unit,method way,double loss_rate,int before_date,QVector<detail> detail);
    void Insert_Request(QString part_no,QDate date,int number);
    void Add_Store(QString part_no,int num1,int num2);
    part Check_Part(QString part_no){return checker.Check_Part(part_no);}
    QVector<request> Calculate();
};

#endif // TIMELINE_H
