#ifndef PERSONALWIDGET_H
#define PERSONALWIDGET_H

#include <QtCore/qglobal.h>
#include "src/containerwidget.h"



class PersonalWidget : public ContainerWidget
{
public:
    PersonalWidget(mongocxx::database* _db , bsoncxx::document::value personelValue = document{}.extract());


    Signal<NoClass> &ClickRequestLogin();

    Signal<NoClass> &ClickNewKonu();
private:
    Signal<NoClass> _ClickRequestLogin;

    void initPersonel();

    Signal<NoClass> _ClickNewKonu;

};


#endif // PERSONALWIDGET_H
