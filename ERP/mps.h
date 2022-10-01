#ifndef MPS_H
#define MPS_H
#include<QString>
#include<QDate>
class MPS
{
    private:
    QString name;
    int number;
    QDate date;
public:
    MPS(){}
    MPS(QString name,int number,QDate date):name(name),number(number),date(date){}
    QString Get_Name(){return this->name;}
    int Get_Number(){return this->number;}
    QDate Get_Date(){return this->date;}
    void Input(QString name,int number,QDate date);
};



#endif // MPS_H
