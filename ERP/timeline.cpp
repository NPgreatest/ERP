﻿#include "timeline.h"
#include<QDebug>

bool Request_Compare(request r1, request r2) {
    bool res=r1.Get_Date()<r2.Get_Date();
    return res;
}
timeline::timeline()
{

}

void timeline::Insert_Part(QString part_no, QString name, QString unit, method way, double loss_rate, int before_date,QVector<detail> detail)
{
     part temp=part(part_no,name,unit,way,loss_rate,before_date);
     temp.Set_Detail(detail);
     checker.Insert_Part(temp);
}

void timeline::Insert_Request(QString part_no, QDate date, int number)
{
    requests.push_back(request(part_no,date,number/(1-checker.Check_Part(part_no).Get_Loss())));
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
                ,(double)(requests[i].Get_Num() * checker.Check_Part(requests[i].Get_part()).Get_Detail()[k].num)
                /(double)(1-checker.Check_Part(checker.Check_Part(requests[i].Get_part()).Get_Detail()[k].child_no).Get_Loss())
                ));
            }
        }
    }
}

void timeline::Sort_By_Date()
{
    qSort(requests.begin(),requests.end(),Request_Compare);

}

void timeline::Calculate_Time()
{
    for(int i=0;i<requests.size();i++){
        if(checker.Check_Part(requests[i].Get_part()).Get_Way()==method::purchase){
            requests[i].Insert_Ahead(-checker.Check_Part(requests[i].Get_part()).Get_Detail()[0].purchase_date+
                    -checker.Check_Part(requests[i].Get_part()).Get_Detail()[0].move_date);
        }else{
            requests[i].Insert_Ahead(-checker.Check_Part(requests[i].Get_part()).Get_Before_Date());
        }
    }
}

void timeline::Calculate_Store()
{
    for(int i=0;i<requests.size();i++){
        if(store.Check_Remin(requests[i].Get_part())!=QPair<int,int>(0,0)){
            if(store.Check_Remin(requests[i].Get_part()).first>=requests[i].Get_Num()){
                store.Add_Store(requests[i].Get_part(),
                QPair<int,int>(store.Check_Remin(requests[i].Get_part()).first-requests[i].Get_Num(),
                store.Check_Remin(requests[i].Get_part()).second));
                requests[i].Alter_Num(-requests[i].Get_Num());
            }else{
                requests[i].Alter_Num(-store.Check_Remin(requests[i].Get_part()).first);
                store.Add_Store(requests[i].Get_part(),QPair<int,int>(0,store.Check_Remin(requests[i].Get_part()).second));
            }
            if(store.Check_Remin(requests[i].Get_part()).second>=requests[i].Get_Num()){
                store.Add_Store(requests[i].Get_part(),
                QPair<int,int>(store.Check_Remin(requests[i].Get_part()).first,
                store.Check_Remin(requests[i].Get_part()).second-requests[i].Get_Num()));
                requests[i].Alter_Num(-requests[i].Get_Num());
            }else{
                requests[i].Alter_Num(-store.Check_Remin(requests[i].Get_part()).second);
                store.Add_Store(requests[i].Get_part(),QPair<int,int>(store.Check_Remin(requests[i].Get_part()).second,0));
            }
        }
    }
}


QVector<request> timeline::Calculate()
{
    DFS_sort();
    Sort_By_Date();
    Calculate_Time();
    Calculate_Store();
    return  requests;
}
