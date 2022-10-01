#include "store.h"
#include<QtDebug>
store::store()
{

}

void store::Add_Store(QString part_no, QPair<int, int> num)
{
    if(hash.find(part_no) == hash.end()){

        hash.insert(part_no,num);
    }else{
        QPair<int, int> temp=hash.find(part_no).value();
        temp.first+=num.first;
        temp.second+=num.second;
        hash[hash.find(part_no).key()]=temp;
    }
}

QPair<int, int> store::Check_Remin(QString part_no)
{
    return hash.find(part_no).value();
}
