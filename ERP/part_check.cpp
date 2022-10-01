#include "part_check.h"

part_check::part_check()
{

}

part part_check::Check_Part(QString part_no)
{
    if(hash.find(part_no)==hash.end())
        return part();
    return hash.find(part_no).value();
}

void part_check::Insert_Part(part part)
{
    hash.insert(part.Get_PartNo(),part);
}
