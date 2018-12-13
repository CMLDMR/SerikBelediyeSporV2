#include "haberdetail.h"

HaberDetail::HaberDetail(mongocxx::database *_db, const std::string &oid)
    :ContainerWidget (_db) , mOid(oid)
{

    addWidget(cpp14::make_unique<WText>(mOid));

}
