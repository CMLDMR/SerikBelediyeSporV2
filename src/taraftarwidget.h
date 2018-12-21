#ifndef TARAFTARWIDGET_H
#define TARAFTARWIDGET_H

#include <QtCore/qglobal.h>
#include "containerwidget.h"



class Body;
class TaraftarItem;
class PersonalWidget;


class TaraftarWidget : public ContainerWidget
{
public:
    TaraftarWidget( mongocxx::database* _db , const int &limit = 5 , const int &skip = 0 );

    Signal<NoClass> &ClickTaraftar();

private:
    Signal<NoClass> _ClickTaraftar;


};





#endif // TARAFTARWIDGET_H
