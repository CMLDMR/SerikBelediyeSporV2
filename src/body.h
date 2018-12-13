#ifndef BODY_H
#define BODY_H

#include "containerwidget.h"

class Body : public ContainerWidget
{
public:
    Body(mongocxx::database* _db);
    void initBody();
    void initHaber(std::string mOid);
    void initDirectHaber( const std::string& mOid);



private:
    WContainerWidget* mMainContainer;
};

#endif // BODY_H
