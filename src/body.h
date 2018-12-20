#ifndef BODY_H
#define BODY_H

#include "containerwidget.h"

class Body : public ContainerWidget
{
public:
    Body(mongocxx::database* _db);
    void initBody();

    void initKurumsal();


    void initHaber(std::string mOid);
    void initDirectHaber( const std::string& mOid);
    void initHaberList();

    void initDuyuru( std::string mOid );
    void initDirectDuyuru(std::string mOid , WContainerWidget *container);
    void initDuyuruList( std::string mOid = "" );


    void initTakimlar(std::string oid);

    void initFotoVideoGalery();


    void initHakkinda();



    void initTaraftarPage();



private:
    WContainerWidget* mMainContainer;
};

#endif // BODY_H
