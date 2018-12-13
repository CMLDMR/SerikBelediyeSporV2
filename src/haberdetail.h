#ifndef HABERDETAIL_H
#define HABERDETAIL_H

#include "containerwidget.h"


class HaberDetail : public ContainerWidget
{
public:
    HaberDetail( mongocxx::database* _db , const std::string& oid );


private:
    std::string mOid;
};

#endif // HABERDETAIL_H
