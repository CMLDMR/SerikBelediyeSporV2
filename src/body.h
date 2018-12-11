#ifndef BODY_H
#define BODY_H

#include "containerwidget.h"

class Body : public ContainerWidget
{
public:
    Body(mongocxx::database* _db);


    void initBody();

private:
    WContainerWidget* mMainContainer;
};

#endif // BODY_H
