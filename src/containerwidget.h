#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WCssDecorationStyle.h>

#include "bootstrap.h"
#include "inlinestyle.h"

#include <string>


#include "mongocxx.h"


using namespace Wt;

class ContainerWidget : public WContainerWidget
{
public:
    ContainerWidget(mongocxx::database* db_);

///
/// \brief addBackGroundImage
/// \param imgpath
/// Set image to Widget Background
void setBackGroundImage( const std::string& imgpath );

///
/// \brief setBackGroundColor
/// \param color
/// set color to Background
void setBackGroundColor( const std::string& color );
void setBackGroundRGB( int red , int green , int blue );
void setBackGroundRGBA( int red , int green , int blue , double alpha = 1.0 );
void setBackGroundRGBRandom( int begin = 0 , int end = 255 );
void setBackGroundRGBRandomAplha(int alpha = 100 , int begin = 0 , int end = 255 );

///
/// \brief setBorder
/// \param color
/// setborder containerWidget Border with color
void setBorder(StandardColor color = StandardColor::White );


///
/// \brief setLeftSide
/// \param inpixel
/// set Left side Space if Container Aligned in ABSOLUTE|STATIC|FIXED
void setLeftSide( int inpixel = 0 );

///
/// \brief setTopSide
/// \param inpixel
/// set Top side space if Container Aligned in ABSOLUTE|STATIC|FIXED
void setTopSide( int inpixel = 0 );

///
/// \brief setRightSide
/// \param pixel
/// set Right side Space if Container Aligned in ABSOLUTE|STATIC|FIXED
void setRightSide( int pixel = 0 );

///
/// \brief setBottomSide
/// \param pixel
/// set Bottom side Space if Container Aligned in ABSOLUTE|STATIC|FIXED
void setBottomSide( int pixel = 0 );

///
/// \brief collection
/// \param collectionname
/// \return
/// get Collectio  of Database
mongocxx::collection collection(const std::string &collectionname );


///
/// \brief db
/// \return
/// get Database pointer indicator
mongocxx::database* db() const;

private:

    mongocxx::database* mdb;


    ///
    /// \brief setSideSpaces
    /// Prepare and Set Style Attribute
    void updateStyle();

    std::string mLeftSpace;
    std::string mRightSpace;
    std::string mTopSpace;
    std::string mBottomSpace;
    std::string mBackGroundImg; // back ground image


    int getRandom( int begin , int end );



};

#endif // CONTAINERWIDGET_H