#ifndef FOTOVIDEOWIDGET_H
#define FOTOVIDEOWIDGET_H

#include "containerwidget.h"

class FotoVideoWidget : public ContainerWidget
{
public:
    FotoVideoWidget(mongocxx::database* _db);


    Signal<NoClass> &ClickGaleri();

private:
    Signal<NoClass> _ClickGaleri;


    void initFotoVideoWidget( WContainerWidget* rContainer);
};



class FotoVideoWidgetItem : public WContainerWidget
{
public:
    FotoVideoWidgetItem(std::string iconPath , std::string year );


private:
};



class FotoVideoGaleri : public ContainerWidget
{
public:
    FotoVideoGaleri(mongocxx::database* _db);
};



#endif // FOTOVIDEOWIDGET_H
