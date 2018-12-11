#ifndef SLIDER_H
#define SLIDER_H

#include "containerwidget.h"



const int __Height = 600;


class Slider : public ContainerWidget
{
public:
    Slider(mongocxx::database* _db);


private:
    WStackedWidget* stackWidget;
};






class SlideItem : public ContainerWidget
{
public:
    SlideItem(mongocxx::database* _db,const int index_ = 0);


    int getIndex() const;

private:
    int index;
};

#endif // SLIDER_H
