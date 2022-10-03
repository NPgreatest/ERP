#ifndef REQUEST_H
#define REQUEST_H
#include<QDate>


class request
{
    QString part_no;
    QDate date;
    int num;
    int ahead;
public:

    QString Get_part(){return part_no;}
    QDate Get_Date(){return date;}
    int Get_Num(){return num;}
    int Get_ahead(){return ahead;}
        request();
    request(QString part_no,QDate date,int num):part_no(part_no),date(date),num(num){}
    void Insert_Ahead(int ahead){this->ahead=ahead;}
    void Alter_Num(int num){this->num+=num;}
};


#endif // REQUEST_H
