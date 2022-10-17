#ifndef PART_CHECK_H
#define PART_CHECK_H
#include<QHash>
#include"part.h"
class part_check
{
    QHash<QString,part> hash;
public:
    part_check();
    part Check_Part(QString part_no);
    void Insert_Part(part part);
};

#endif // PART_CHECK_H
