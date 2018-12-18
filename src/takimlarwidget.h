#ifndef TAKIMLARWIDGET_H
#define TAKIMLARWIDGET_H

#include "containerwidget.h"

class TakimlarWidget : public ContainerWidget
{
public:
    TakimlarWidget(mongocxx::database* _db);

    Signal<std::string> &ClickTakim();


private:

    void addTakim(const std::string &oid , const std::string &takimadi, const std::string& backurl , WContainerWidget* rContainer);

    Signal<std::string> _ClickTakim;
};





class TakimlarPage : public ContainerWidget
{
public:
    TakimlarPage(mongocxx::database* _db , const std::string &takimOid = "" );


    bsoncxx::document::view currentTakimView() const;
//    void setCurrentTakimView(const bsoncxx::document::view &currentTakimView);

private:
    void initTakim( std::string takimoid );


    void initMenuContent(const std::string& menu);
    WContainerWidget* mIcerikContainer;


    bsoncxx::document::value mCurrentTakimValue;
};




#endif // TAKIMLARWIDGET_H
