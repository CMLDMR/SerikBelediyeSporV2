#ifndef HEADER_H
#define HEADER_H

#include "containerwidget.h"

class Header : public ContainerWidget
{
public:
    Header(mongocxx::database* db);



    Signal<NoClass> &ClickAnaSayfa();

    Signal<NoClass> &ClickHaberler();

    Signal<NoClass> &ClickDuyurular();

private:

    void PlaceLogo();

    void PlaceSerik();

    void PlaceToolBar();



    ContainerWidget* mContentContainer;


    Signal<NoClass> _ClickAnasayfa;

    Signal<NoClass> _ClickHaberler;

    Signal<NoClass> _ClickDuyurular;
};

#endif // HEADER_H
