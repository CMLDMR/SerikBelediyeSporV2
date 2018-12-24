#ifndef CEVAPITEM_H
#define CEVAPITEM_H

#include <QtCore/qglobal.h>
#include "src/containerwidget.h"

class CevapItem : public ContainerWidget
{
public:
    CevapItem( mongocxx::database* _db , bsoncxx::document::view _view);


private:
    bsoncxx::document::view mView;
};

#endif // CEVAPITEM_H
