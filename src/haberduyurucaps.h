#ifndef HABERDUYURUCAPS_H
#define HABERDUYURUCAPS_H


#include "containerwidget.h"

class HaberDuyuruCaps : public ContainerWidget
{
public:
    HaberDuyuruCaps(mongocxx::database* _db);
};



class HaberDuyuruCapsItem : public ContainerWidget
{
public:
    HaberDuyuruCapsItem(mongocxx::database* _db , bool m_Haber = false );
};






#endif // HABERDUYURUCAPS_H
