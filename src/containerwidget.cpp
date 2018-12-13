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
    mBackGroundImg = Style::background::url(imgpath)+Style::background::size::cover+Style::background::repeat::norepeat;
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

void ContainerWidget::setLeftSide(double inPercent)
{
    mLeftSpace = "left:"+std::to_string(inPercent)+"%;";
    this->updateStyle();
}

void ContainerWidget::setTopSide(int inpixel)
{
    mRightSpace = "top:"+std::to_string(inpixel)+"px;";
    this->updateStyle();
}

void ContainerWidget::setTopSide(double inPercent)
{
    mRightSpace = "top:"+std::to_string(inPercent)+"%;";
    this->updateStyle();
}

void ContainerWidget::setRightSide(int pixel)
{
    mTopSpace = "right:"+std::to_string(pixel)+"px;";
    updateStyle();
}

void ContainerWidget::setRightSide(double inPercet)
{
    mTopSpace = "right:"+std::to_string(inPercet)+"%;";
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

std::string ContainerWidget::downloadFile(std::string oid, bool forceFilename)
{

    auto Bucket = this->db()->gridfs_bucket();

    if( QFile::exists( QString("docroot/tempfile/%1.indexed").arg(oid.c_str()) ) )
    {
        QFile file(QString("docroot/tempfile/%1.indexed").arg(oid.c_str()));
        if( file.open(QIODevice::ReadOnly) )
        {
            QString fileName = QString::fromUtf8(file.readAll());
            file.close();
            return fileName.toStdString();
        }
    }else{
        std::cout << "FILE NOT FOUND" << QString("docroot/tempfile/%1.indexed").arg(oid.c_str()).toStdString() << std::endl;
    }




    auto doc = bsoncxx::builder::basic::document{};

    try {
        doc.append(bsoncxx::builder::basic::kvp("key",bsoncxx::oid{oid}));
    } catch (bsoncxx::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return "img/404-header.png";
    }



    mongocxx::gridfs::downloader downloader;
    try {
        auto roid = bsoncxx::types::value(doc.view()["key"].get_oid());
        downloader = Bucket.open_download_stream(roid);

    } catch (bsoncxx::exception &e) {
        return "img/error.png";
    }


    auto file_length = downloader.file_length();
    auto bytes_counter = 0;

    QFileInfo info( downloader.files_document()["filename"].get_utf8().value.to_string().c_str() );

    QString fullFilename;

    if( forceFilename )
    {
        fullFilename = QString("tempfile/%1").arg(downloader.files_document()["filename"].get_utf8().value.to_string().c_str());
    }else{
        fullFilename = QString("tempfile/%2.%1").arg(info.suffix())
                           .arg(downloader.files_document()["md5"].get_utf8().value.to_string().c_str());
    }

    //        if( QFile::exists("docroot/"+fullFilename) )
    //        {
    //            return fullFilename.toStdString();
    //        }

    auto buffer_size = std::min(file_length, static_cast<std::int64_t>(downloader.chunk_size()));
    auto buffer = bsoncxx::stdx::make_unique<std::uint8_t[]>(static_cast<std::size_t>(buffer_size));

    std::ofstream out;

    out.open("docroot/"+fullFilename.toStdString(),std::ios::out | std::ios::app | std::ios::binary);


    if( out.is_open() )
    {

        while ( auto length_read = downloader.read(buffer.get(), static_cast<std::size_t>(buffer_size)) ) {

            auto bufferPtr = buffer.get();
            std::cout << "Size Of: " << sizeof ( bufferPtr ) << std::endl;
            out.write( reinterpret_cast<char*>( bufferPtr ) , length_read );

            bytes_counter += static_cast<std::int32_t>( length_read );
            //                std::cout << "Downloaded: " << file_length << "/" << bytes_counter << " lengRead :" << length_read << " Buffer Size: " << buffer_size << std::endl;

        }

        out.close();
    }

    else{
        std::cout << "Error Can Not Open File: " <<"docroot/"+fullFilename.toStdString() << std::endl;
        return "img/error.png";
    }


    QFile file(QString("docroot/tempfile/%1.indexed").arg(oid.c_str()));
    if( file.open(QIODevice::ReadWrite) )
    {
        file.write(fullFilename.toUtf8());
        file.close();
    }else{
        std::cout << "FILE CAN NOT CREATED: " << file.fileName().toStdString() << fullFilename.toStdString() << std::endl;
    }

    std::cout << "FILE FORCED : " << forceFilename <<" FILE FILL: " << fullFilename.toStdString() <<" TOTHIS FILE: " << file.fileName().toStdString() << std::endl;

    return fullFilename.toStdString();
}

std::string ContainerWidget::getErroImgPath() const
{
    return "img/404-header.png";
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
