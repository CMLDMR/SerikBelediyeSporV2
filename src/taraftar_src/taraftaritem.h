#ifndef TARAFTARITEM_H
#define TARAFTARITEM_H

#include <QtCore/qglobal.h>
#include "src/containerwidget.h"

class TaraftarItem : public ContainerWidget
{
public:
    TaraftarItem( mongocxx::database* _db , bsoncxx::document::view _view );


    Signal<std::string> &ClickTaraftarItem();

private:

    bsoncxx::document::value mValue;

    Signal<std::string> _ClickTaraftarItem;
};


#endif // TARAFTARITEM_H
