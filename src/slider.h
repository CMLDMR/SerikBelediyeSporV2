#ifndef SLIDER_H
#define SLIDER_H

#include "containerwidget.h"



const int __Height = 600;


class Slider : public ContainerWidget
{
public:
    Slider(mongocxx::database* _db);



    Signal<std::string> &mClick();

private:
    WStackedWidget* stackWidget;

    Signal<std::string> _mClick;
};






class SlideItem : public ContainerWidget
{
public:
    SlideItem( mongocxx::database* _db , const int index_ = 0 );

    int getIndex() const;

    Signal<std::string> &Click();

    std::string getOid() const;

    std::string getTitle() const;
    void setTitle(const std::string &title);

    std::string getBackGroundImg() const;
    void setBackGroundImg(const std::string &backGroundImg);

    std::string getPlainText() const;
    void setPlainText(const std::string &plainText);




private:
    int index;

    Signal<std::string> _mClick;

    std::string mOid;
    void setOid(const std::string &oid);


    std::string mTitle;
    std::string mBackGroundImg;
    std::string mPlainText;


    WText* mTextTitle;
    void setTextTitle( const std::string& textTitle);

    WText* mSmallText;
    void setSmallText( const std::string& smallText);

};

#endif // SLIDER_H
