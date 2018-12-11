#ifndef FOTOVIDEOWIDGET_H
#define FOTOVIDEOWIDGET_H

#include "containerwidget.h"

class FotoVideoWidget : public ContainerWidget
{
public:
    FotoVideoWidget(mongocxx::database* _db);
};

#endif // FOTOVIDEOWIDGET_H
