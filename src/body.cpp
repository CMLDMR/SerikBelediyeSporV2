#include "body.h"

#include "slider.h"
#include "haberduyurucaps.h"
#include "takimlarwidget.h"
#include "fotovideowidget.h"
#include "iletisimwidget.h"


#include <Wt/WApplication.h>



Body::Body(mongocxx::database *_db)
    :ContainerWidget (_db)
{
    setMargin(0,AllSides);

    addStyleClass(Bootstrap::Grid::container_fluid);

    mMainContainer = addWidget(cpp14::make_unique<WContainerWidget>());

    mMainContainer->addStyleClass(Bootstrap::Grid::row);

    this->initBody();
}

void Body::initBody()
{
    mMainContainer->clear();

    auto slider = mMainContainer->addWidget(cpp14::make_unique<Slider>(this->db()));
    slider->addStyleClass(Bootstrap::Grid::col_full_12);
    slider->mClick().connect(this,&Body::initHaber);

    auto haberDuyuruCaps = mMainContainer->addWidget(cpp14::make_unique<HaberDuyuruCaps>(this->db()));
    haberDuyuruCaps->addStyleClass(Bootstrap::Grid::col_full_12);
    haberDuyuruCaps->ClickHaber().connect(this,&Body::initHaber);
    haberDuyuruCaps->ClickDuyuru().connect(this,&Body::initDuyuru);


    auto takimlarWidget = mMainContainer->addWidget(cpp14::make_unique<TakimlarWidget>(this->db()));
    takimlarWidget->addStyleClass(Bootstrap::Grid::col_full_12);

    auto fotoVideoWidget = mMainContainer->addWidget(cpp14::make_unique<FotoVideoWidget>(this->db()));
    fotoVideoWidget->addStyleClass(Bootstrap::Grid::col_full_12);

    auto iletisimWidget = mMainContainer->addWidget(cpp14::make_unique<IletisimWidget>(this->db()));
    iletisimWidget->addStyleClass(Bootstrap::Grid::col_full_12);

//    wApp->setInternalPath("");
}

void Body::initHaber(std::string mOid)
{

    this->initDirectHaber(mOid);

    wApp->instance()->setInternalPath(u8"col=Haberler&oid="+mOid);

}

void Body::initDirectHaber(const std::string &mOid)
{
    mMainContainer->clear();


    auto filter = document{};

    try {
        filter.append(kvp("_id",bsoncxx::oid(mOid))) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << "-> filter." << "_id :"<< e.what() << std::endl;
    }


    try {
        auto val = this->db()->collection("Haberler").find_one(filter.view());


        if( !val ){
            std::cout << "Line: " << __LINE__ << " -> No Document Entry";
        }else{

            auto view = val.value().view();

            auto container = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            container->addStyleClass(Bootstrap::Grid::col_full_12);
            container->setContentAlignment(AlignmentFlag::Center);

            // Başlık Kısmı
            {

                auto _Container = container->addWidget(cpp14::make_unique<WContainerWidget>());
                _Container->setHeight(150);
                _Container->setMaximumSize(1350,WLength::Auto);

                auto imgContainer = _Container->addWidget(cpp14::make_unique<WContainerWidget>());
                imgContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0,0.7));
                imgContainer->setWidth(WLength("100%"));
                imgContainer->setHeight(WLength("100%"));
                imgContainer->setMargin(0,AllSides);

                try {
                    auto value = view["habericon"].get_oid().value.to_string();
                _Container->setAttributeValue(Style::style,Style::background::url(this->downloadFile(value))
                                                      +Style::background::size::cover
                                                      +Style::background::repeat::norepeat);
                _Container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
                _Container->setPadding(1,AllSides);
                _Container->setWidth(WLength("100%"));
                } catch (bsoncxx::exception &e) {
                    std::cout << "Line " << __LINE__ << "->in view habericon type is not " << "oid() :"<< e.what() << std::endl;
                _Container->setAttributeValue(Style::style,Style::background::url(this->getErroImgPath())
                                                      +Style::background::size::cover
                                                      +Style::background::repeat::norepeat);
                }

                auto vLayout = imgContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
                auto _title = vLayout->addWidget(cpp14::make_unique<WText>(),0,AlignmentFlag::Center|AlignmentFlag::Middle);

                try {
                    auto value = view["baslik"].get_utf8().value.to_string();
                    _title->setText(value);
                } catch (bsoncxx::exception &e) {
                    std::cout << "Line " << __LINE__ << "->in view baslik type is not " << "get_utf8() :"<< e.what() << std::endl;
                }
                _title->setAttributeValue(Style::style,Style::font::size::s28px+Style::color::rgb("255,255,255")+Style::font::weight::bold+Style::font::family::tahoma);

            }


            // İcerikteki Dosyaların indirilmesi
            {

                try {
                    auto value = view["dosyalar"].get_array().value;
                    for( auto item : value )
                    {
                        this->downloadFile(item.get_oid().value.to_string(),true);
                    }
                } catch (bsoncxx::exception &e) {
                    std::cout << "Line " << __LINE__ << "->in view dosyalar type is not " << "get_array() :"<< e.what() << std::endl;
                }

            }


            // İçerik Kısmı
            {
                auto _Container = container->addWidget(cpp14::make_unique<WContainerWidget>());
                _Container->setMaximumSize(1200,WLength::Auto);
                _Container->setContentAlignment(AlignmentFlag::Justify);
                _Container->addStyleClass(Bootstrap::ImageShape::img_rounded);
                auto _text = _Container->addWidget(cpp14::make_unique<WText>(" HTML CONTENT " , TextFormat::UnsafeXHTML));


                try {
                    auto value = view["html"].get_utf8().value.to_string().c_str();
                    std::cout << "Set TEXT: " << _text->setText(value) << std::endl;
                    _text->setMaximumSize(1024,WLength::Auto);
                } catch (bsoncxx::exception &e) {
                    std::cout << "Line " << __LINE__ << "->in view html type is not " << "get_utf8() :"<< e.what() << std::endl;
                }

            }

        }



    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
    }

}

void Body::initHaberList()
{

    mMainContainer->clear();



    auto filter = document{};

    try {
        filter.append(kvp("yayinda",bsoncxx::types::b_bool{true})) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> filter." << "yayinda :"<< e.what() << std::endl;
    }


    auto sortDoc = document{};

    try {
        sortDoc.append(kvp("_id",-1)) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> sortDoc." << "_id :"<< e.what() << std::endl;
    }

    mongocxx::options::find findOptions;

    findOptions.limit(12);
    findOptions.sort(sortDoc.view());



    try {
        auto cursor = this->db()->collection("Haberler").find(filter.view(),findOptions);


        auto ContentContainer = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        ContentContainer->addStyleClass(Bootstrap::Grid::col_full_12);
        ContentContainer->setContentAlignment(AlignmentFlag::Center);

        auto rContainer = ContentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        rContainer->addStyleClass(Bootstrap::Grid::row);
        rContainer->setMaximumSize(1200,WLength::Auto);


        for( auto doc : cursor )
        {

            auto _container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
            _container->decorationStyle().setCursor(Cursor::PointingHand);

            // Click Oid
            {
                try {
                    auto value = doc["_id"].get_oid().value.to_string();
                    _container->clicked().connect([=](){
                        this->initHaber(value);
                    });
                } catch (bsoncxx::exception &e) {
                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "->in doc _id type is not " << "get_oid() :"<< e.what() << std::endl;
                }
            }


            _container->setMargin(10,Side::Bottom);

            auto container = _container->addWidget(cpp14::make_unique<WContainerWidget>());
            container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
            container->setAttributeValue(Style::style,Style::background::color::rgba(245,245,245));
            container->setHeight(240);
            auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

            // Resim
            {
                auto imgContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
                imgContainer->setWidth(WLength("100%"));
                imgContainer->setHeight(180);
                imgContainer->addStyleClass(Bootstrap::ImageShape::img_circle);
                try {
                    auto value = doc["habericon"].get_oid().value.to_string();
                    imgContainer->setAttributeValue(Style::style,Style::background::url(this->downloadFile(value))+Style::background::size::cover+Style::background::repeat::norepeat);
                } catch (bsoncxx::exception &e) {
                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "->in doc habericon type is not " << "get_oid() :"<< e.what() << std::endl;
                    imgContainer->setAttributeValue(Style::style,Style::background::url(this->getErroImgPath()));
                }
            }

            // Haber Başlığı
            {

                try {
                    auto value = doc["baslik"].get_utf8().value.to_string();
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(value));
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::font::family::tahoma);
                } catch (bsoncxx::exception &e) {
                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "->in doc baslik type is not " << "get_utf8() :"<< e.what() << std::endl;
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(e.what()));
                }

            }

        }



    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
    }








}

void Body::initDuyuru(std::string mOid)
{
    this->initDirectDuyuru(mOid);

    wApp->instance()->setInternalPath(u8"col=Duyurular&oid="+mOid);
}

void Body::initDirectDuyuru(std::string mOid)
{

    std::cout << __LINE__ << " " <<__FUNCTION__ << " : "<<mOid << std::endl;

    mMainContainer->clear();


    auto filter = document{};

    try {
        filter.append(kvp("_id",bsoncxx::oid(mOid))) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << "-> filter." << "_id :"<< e.what() << std::endl;
    }


    try {
        auto val = this->db()->collection("Duyurular").find_one(filter.view());


        if( !val ){
            std::cout << "Line: " << __LINE__ << " -> No Document Entry";
        }else{

            auto view = val.value().view();

            auto container = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            container->addStyleClass(Bootstrap::Grid::col_full_12);
            container->setContentAlignment(AlignmentFlag::Center);

            // Başlık Kısmı
            {

                auto _Container = container->addWidget(cpp14::make_unique<WContainerWidget>());
                _Container->setHeight(150);
                _Container->setMaximumSize(1350,WLength::Auto);

                auto imgContainer = _Container->addWidget(cpp14::make_unique<WContainerWidget>());
                imgContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));
                imgContainer->setWidth(WLength("100%"));
                imgContainer->setHeight(WLength("100%"));

            _Container->setAttributeValue(Style::style,Style::background::url("test/3.jpg")
                                                  +Style::background::size::cover
                                                  +Style::background::repeat::norepeat);

//                try {
//                    auto value = view["habericon"].get_oid().value.to_string();
//                _Container->setAttributeValue(Style::style,Style::background::url(this->downloadFile(value))
//                                                      +Style::background::size::cover
//                                                      +Style::background::repeat::norepeat);
//                } catch (bsoncxx::exception &e) {
//                    std::cout << "Line " << __LINE__ << "->in view habericon type is not " << "oid() :"<< e.what() << std::endl;
//                _Container->setAttributeValue(Style::style,Style::background::url(this->getErroImgPath())
//                                                      +Style::background::size::cover
//                                                      +Style::background::repeat::norepeat);
//                }

                auto vLayout = imgContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
                auto _title = vLayout->addWidget(cpp14::make_unique<WText>(),0,AlignmentFlag::Center|AlignmentFlag::Middle);

                try {
                    auto value = view["baslik"].get_utf8().value.to_string();
                    _title->setText(value);
                } catch (bsoncxx::exception &e) {
                    std::cout << "Line " << __LINE__ << "->in view baslik type is not " << "get_utf8() :"<< e.what() << std::endl;
                }
                _title->setAttributeValue(Style::style,Style::font::size::s24px+Style::color::rgb("255,255,255")+Style::font::weight::bold);

            }


            // İcerikteki Dosyaların indirilmesi
            {

//                try {
//                    auto value = view["dosyalar"].get_array().value;
//                    for( auto item : value )
//                    {
//                        this->downloadFile(item.get_oid().value.to_string(),true);
//                    }
//                } catch (bsoncxx::exception &e) {
//                    std::cout << "Line " << __LINE__ << "->in view dosyalar type is not " << "get_array() :"<< e.what() << std::endl;
//                }

            }


            // İçerik Kısmı
            {
                auto _Container = container->addWidget(cpp14::make_unique<WContainerWidget>());
                _Container->setMaximumSize(1200,WLength::Auto);
                _Container->setContentAlignment(AlignmentFlag::Justify);
                _Container->setMargin(20,Side::Top|Side::Bottom);
                _Container->setPadding(10,AllSides);
                _Container->setAttributeValue(Style::style,Style::background::color::rgba(155,155,155)+Style::Border::border("1px solid black"));


                auto _text = _Container->addWidget(cpp14::make_unique<WText>(" HTML CONTENT " , TextFormat::UnsafeXHTML));


                try {
                    auto value = view["icerik"].get_utf8().value.to_string();
//                    std::cout << "HTML: "<<value << std::endl;
                    std::cout << "Set TEXT: " << _text->setText(value) << std::endl;

                    _text->setMaximumSize(1024,WLength::Auto);


                } catch (bsoncxx::exception &e) {
                    std::cout << "Line " << __LINE__ << "->in view html type is not " << "get_utf8() :"<< e.what() << std::endl;
                }

            }

        }



    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
    }

}
