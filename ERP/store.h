#ifndef STORE_H
#define STORE_H
#include<QHash>
#include<QPair>


class store
{
    QHash<QString,QPair<int,int>> hash;
public:
    store();
    void Add_Store(QString part_no,QPair<int,int> num);
    QPair<int,int> Check_Remin(QString part_no);
};

#endif // STORE_H
