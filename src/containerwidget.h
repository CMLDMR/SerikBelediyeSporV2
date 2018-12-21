#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WSpinBox.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WSignal.h>
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>
#include <Wt/WDialog.h>
#include <Wt/WMessageBox.h>

#include "bootstrap.h"
#include "inlinestyle.h"

#include <string>
#include <vector>
#include <memory>


#include "mongocxx.h"

#include <fstream>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QFileInfo>
#include <QDate>



using namespace Wt;


class Person
{

public:

    Person( bsoncxx::document::view view = bsoncxx::builder::basic::document{}.view() );

    std::string getIsim() const;

    std::string getTel() const;

    std::string getSifre() const;

    bsoncxx::oid getOid() const;

    bool getLogined() const ;

    void setPersonelView( bsoncxx::document::value value );

    void setLogined( bool logined );

private:

    bsoncxx::document::view mView;

    bool mLogined;

};





class ContainerWidget : public WContainerWidget , public Person
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
/// \brief setLogin
/// \param telnumber
/// \param pasword
/// Login Personel Information
void setLogin( std::string telnumber , std::string pasword );

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
/// \brief setLeftSide
/// \param inPercent
/// set Left Side Space if Container Aligned in ABSOLUTE|STATIC|FIXED
void setLeftSide( double inPercent = 0.0 );

///
/// \brief setTopSide
/// \param inpixel
/// set Top side space if Container Aligned in ABSOLUTE|STATIC|FIXED
void setTopSide( int inpixel = 0 );

///
/// \brief setTopSide
/// \param inPercent
/// set Top side Space if Container Aligned ABSOLUTE|STATIC|FIXED
void setTopSide( double inPercent = 0.0 );

///
/// \brief setRightSide
/// \param pixel
/// set Right side Space if Container Aligned in ABSOLUTE|STATIC|FIXED
void setRightSide( int pixel = 0 );

///
/// \brief setRightSide
/// \param inPercet
/// set Right side Space if Container Aligned in ABSOLUTE|STATIC|FIXED
void setRightSide( double inPercet = 0 );

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
/// \brief downloadFile
/// \param oid
/// \param forceFilename
/// \return
/// Download image and return its path
std::string downloadFile( std::string oid , bool forceFilename = false );

///
/// \brief getErroImgPath
/// \return
/// Return Error image for Error
std::string getErroImgPath() const;



///
/// \brief db
/// \return
/// get Database pointer indicator
mongocxx::database* db() const;



///
/// \brief ShowMessage
/// \param title
/// \param message
/// Show Message
void ShowMessage( const std::string &title , const std::string &message );

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
