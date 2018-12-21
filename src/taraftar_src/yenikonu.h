#ifndef YENIKONU_H
#define YENIKONU_H

#include <QtCore/qglobal.h>
#include "src/containerwidget.h"

class YeniKonu : public ContainerWidget
{
public:
    YeniKonu( mongocxx::database* db_ );



    Signal<NoClass> &ClickSave();

    std::string html() const;

    std::string title() const;

private:
    WTextEdit* mEditor;
    WLineEdit* mTitleText;


    Signal<NoClass> _ClickSave;
};

#endif // YENIKONU_H
