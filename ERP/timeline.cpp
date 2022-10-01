#include "timeline.h"
#include<QDebug>


timeline::timeline()
{

}

void timeline::Insert_Part(QString part_no, QString name, QString unit, method way, double loss_rate, int before_date,QVector<detail> detail)
{
    if(way==method::purchase){
        checker.Insert_Part(part(part_no,name,unit,way,loss_rate,before_date));
    }else{
        part temp=part(part_no,name,unit,way,loss_rate,before_date);
        temp.Set_Detail(detail);
        checker.Insert_Part(temp);
    }
}

void timeline::Insert_Request(QString part_no, QDate date, int number)
{
    requests.push_back(request(part_no,date,number));
}

void timeline::Add_Store(QString part_no, int num1, int num2)
{
    store.Add_Store(part_no,QPair<int,int>(num1,num2));
}

void timeline::DFS_sort()
{
    for(int i=0;i<requests.size();i++ ){
        if(checker.Check_Part(requests[i].Get_part()).Get_Way()==method::product){
            for(int k=0;k<checker.Check_Part(requests[i].Get_part()).Get_Detail().size();k++){
                requests.insert(1+i+k,request
             (checker.Check_Part(requests[i].Get_part()).Get_Detail()[k].child_no,
             requests[i].Get_Date().addDays(-checker.Check_Part(requests[i].Get_part()).Get_Before_Date())
                ,(requests[i].Get_Num() * checker.Check_Part(requests[i].Get_part()).Get_Detail()[k].num) /// checker.Check_Part(requests[i].Get_part()).Get_Loss()
                ));
            }
        }
    }
}

void timeline::Sort_By_Date()
{

}
QVector<request> timeline::Calculate()
{
    DFS_sort();

    Sort_By_Date();
    return  requests;
}
