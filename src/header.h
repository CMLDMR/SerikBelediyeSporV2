#ifndef HEADER_H
#define HEADER_H

#include "containerwidget.h"

class Header : public ContainerWidget
{
public:
    Header(mongocxx::database* db);



    Signal<NoClass> &ClickAnaSayfa();

    Signal<NoClass> &ClickKurumsal();

    Signal<NoClass> &ClickHaberler();

    Signal<NoClass> &ClickDuyurular();

    Signal<NoClass> &ClickGaleri();

    Signal<NoClass> &ClickHakkinda();

private:

    void PlaceLogo();

    void PlaceSerik();

    void PlaceToolBar();



    WContainerWidget* mContentContainer;


    Signal<NoClass> _ClickAnasayfa;

    Signal<NoClass> _ClickKurumsal;

    Signal<NoClass> _ClickHaberler;

    Signal<NoClass> _ClickDuyurular;

    Signal<NoClass> _ClickGaleri;

    Signal<NoClass> _ClickHakkinda;
};

#endif // HEADER_H
