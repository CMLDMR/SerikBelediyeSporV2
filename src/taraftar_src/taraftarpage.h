#ifndef TARAFTARPAGE_H
#define TARAFTARPAGE_H

#include <QtCore/qglobal.h>
#include "src/containerwidget.h"

class Body;
class PersonalWidget;

class TaraftarPage : public ContainerWidget
{
public:

    TaraftarPage( Body* _mBody );

    void initStartupPage();

    void initItemPage(std::string mOid);

    void initLoginPage();

    void initRegisterPage();

    void initNewKonuPage();



private:

    Body* mBody;

    PersonalWidget* mPersonWidget;

    WContainerWidget* mContainerWidget;

};

#endif // TARAFTARPAGE_H
