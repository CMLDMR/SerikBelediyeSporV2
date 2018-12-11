#ifndef HEADER_H
#define HEADER_H

#include "containerwidget.h"

class Header : public ContainerWidget
{
public:
    Header(mongocxx::database* db);


private:

    void PlaceLogo();

    void PlaceSerik();

    void PlaceToolBar();



    ContainerWidget* mContentContainer;
};

#endif // HEADER_H
