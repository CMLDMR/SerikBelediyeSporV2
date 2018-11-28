#include "containerwidget.h"
#include <random>

ContainerWidget::ContainerWidget(mongocxx::database *db_)
    :WContainerWidget (),mdb(db_)
{

    mLeftSpace = "";
    mRightSpace = "";
    mTopSpace = "";
    mBottomSpace = "";
    mBackGroundImg = "";


}

void ContainerWidget::setBackGroundImage(const std::string &imgpath)
{
    mBackGroundImg = Style::background::url(imgpath);
    updateStyle();
}

void ContainerWidget::setBackGroundColor(const std::string &color)
{
    mBackGroundImg = Style::background::color::color(color);
    updateStyle();
}

void ContainerWidget::setBackGroundRGB(int red, int green, int blue)
{
    mBackGroundImg = Style::background::color::rgb(red,green,blue);
    updateStyle();
}

void ContainerWidget::setBackGroundRGBA(int red, int green, int blue, double alpha)
{
    mBackGroundImg = Style::background::color::rgba(red,green,blue,alpha);
    updateStyle();
}

void ContainerWidget::setBackGroundRGBRandom(int begin, int end)
{
    if( begin > end ) begin = end-1;
    if( begin < 0 ) begin = 0;
    if( end < begin ) end = begin + 1;
    if( end > 255 ) end = 255;

    mBackGroundImg = Style::background::color::rgb(this->getRandom(begin,end),this->getRandom(begin,end),this->getRandom(begin,end));
    updateStyle();
}

void ContainerWidget::setBackGroundRGBRandomAplha(int alpha , int begin, int end )
{
    if( begin > end ) begin = end-1;
    if( begin < 0 ) begin = 0;
    if( end < begin ) end = begin + 1;
    if( end > 255 ) end = 255;

    if( alpha > 100 ) alpha = 100;
    if( alpha < 0 ) alpha = 0;

    double _alpha = static_cast<double>(alpha) / 100;

    mBackGroundImg = Style::background::color::rgba(this->getRandom(begin,end),this->getRandom(begin,end),this->getRandom(begin,end),_alpha);
    updateStyle();

}

void ContainerWidget::setBorder(StandardColor color)
{
    decorationStyle().setBorder(WBorder(BorderStyle::Solid,BorderWidth::Thick,WColor(color)));
}

void ContainerWidget::setLeftSide(int inpixel)
{
    mLeftSpace = "left:"+std::to_string(inpixel)+"px;";
    this->updateStyle();
}

void ContainerWidget::setTopSide(int inpixel)
{
    mRightSpace = "top:"+std::to_string(inpixel)+"px;";
    this->updateStyle();
}

void ContainerWidget::setRightSide(int pixel)
{
    mTopSpace = "right:"+std::to_string(pixel)+"px;";
    updateStyle();
}

void ContainerWidget::setBottomSide(int pixel)
{
    mBottomSpace = "bottom:"+std::to_string(pixel)+"px;";
    updateStyle();
}



mongocxx::collection ContainerWidget::collection(const std::string& collectionname)
{
    return mdb->collection(collectionname);
}

mongocxx::database *ContainerWidget::db() const
{
    return mdb;
}

void ContainerWidget::updateStyle()
{
    std::string str = mLeftSpace+mRightSpace+mTopSpace+mBottomSpace
        +mBackGroundImg;
    setAttributeValue(Style::style,str);
}

int ContainerWidget::getRandom(int begin, int end)
{
    std::random_device rd;
    std::map<int, int> hist;
    std::uniform_int_distribution<int> dist(begin, end);
}
