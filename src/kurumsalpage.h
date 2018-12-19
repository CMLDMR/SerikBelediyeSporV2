#ifndef KURUMSALPAGE_H
#define KURUMSALPAGE_H

#include <QtCore/qglobal.h>

#include "containerwidget.h"

class KurumsalPage : public ContainerWidget
{
public:
    KurumsalPage( mongocxx::database* _db );
};

#endif // KURUMSALPAGE_H
