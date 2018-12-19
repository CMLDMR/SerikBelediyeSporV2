#ifndef TARAFTARWIDGET_H
#define TARAFTARWIDGET_H

#include <QtCore/qglobal.h>
#include "containerwidget.h"

class TaraftarWidget : public ContainerWidget
{
public:
    TaraftarWidget( mongocxx::database* _db );
};




class TaraftarItem : public ContainerWidget
{
public:
    TaraftarItem( mongocxx::database* _db );
};

#endif // TARAFTARWIDGET_H
