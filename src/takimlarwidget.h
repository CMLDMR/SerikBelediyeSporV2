#ifndef TAKIMLARWIDGET_H
#define TAKIMLARWIDGET_H

#include "containerwidget.h"

class TakimlarWidget : public ContainerWidget
{
public:
    TakimlarWidget(mongocxx::database* _db);
};

#endif // TAKIMLARWIDGET_H
