#ifndef TARAFTARWIDGET_H
#define TARAFTARWIDGET_H

#include <QtCore/qglobal.h>
#include "containerwidget.h"



class TaraftarWidget : public ContainerWidget
{
public:
    TaraftarWidget( mongocxx::database* _db , const int &limit = 5 , const int &skip = 0 );

    Signal<NoClass> &ClickTaraftar();

private:
    Signal<NoClass> _ClickTaraftar;


};




class TaraftarItem : public ContainerWidget
{
public:
    TaraftarItem( mongocxx::database* _db );
};



class TaraftarPage : public ContainerWidget
{
public:
    TaraftarPage( mongocxx::database* _db );


    void initLoginPage();

    void initRegisterPage();



private:

};


class PersonalWidget : public ContainerWidget
{
public:
    PersonalWidget(mongocxx::database* _db );


    Signal<NoClass> &ClickRequestLogin();

private:
    Signal<NoClass> _ClickRequestLogin;
};




#endif // TARAFTARWIDGET_H
