#ifndef ILETISIMWIDGET_H
#define ILETISIMWIDGET_H

#include "containerwidget.h"



class IletisimWidget : public ContainerWidget
{
public:
    IletisimWidget(mongocxx::database* _db);
};

#endif // ILETISIMWIDGET_H
