#ifndef PART_H
#define PART_H
#include<QVector>
#include<QString>
enum method{
    product, purchase
};
struct detail{
    QString child_no;
    int num;
    int move_date;
    int purchase_date;
    detail(){}
    detail(QString child_no,int num,int move_date,int purchase_date):child_no(child_no),num(num),move_date(move_date),purchase_date(purchase_date){}
};

class part
{
    QString part_no;
    QString name;
    QString unit;
    method way;
    double loss_rate;
    int before_date;


    QVector<detail> way_to_product;
public:
    part();
    part(QString part_no,QString name,QString unit,method way,double loss_rate,int before_date):
        part_no(part_no),name(name),unit(unit),way(way),loss_rate(loss_rate),before_date(before_date),way_to_product(QVector<detail>()){}
    void Set_Detail(QVector<detail> detail){way_to_product=detail;}

    QString Get_PartNo(){return part_no;}
    QString Get_Name(){return name;}
    QString Get_Unit(){return unit;}
    method Get_Way(){return way;}
    double Get_Loss(){return loss_rate;}
    int Get_Before_Date(){return before_date;}
    QVector<detail> Get_Detail(){return way_to_product;}



};
#endif // PART_H
