#include "body.h"

#include "slider.h"
#include "haberduyurucaps.h"
#include "takimlarwidget.h"
#include "fotovideowidget.h"
#include "iletisimwidget.h"
#include "kurumsalpage.h"
#include "taraftarwidget.h"


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
    haberDuyuruCaps->ClickDuyuru().connect(this,&Body::initDuyuruList);


    auto tarafterWidget = mMainContainer->addWidget(cpp14::make_unique<TaraftarWidget>(this->db()));
    tarafterWidget->addStyleClass(Bootstrap::Grid::col_full_12);


    auto takimlarWidget = mMainContainer->addWidget(cpp14::make_unique<TakimlarWidget>(this->db()));
    takimlarWidget->addStyleClass(Bootstrap::Grid::col_full_12);
    takimlarWidget->ClickTakim().connect(this,&Body::initTakimlar);

    auto fotoVideoWidget = mMainContainer->addWidget(cpp14::make_unique<FotoVideoWidget>(this->db()));
    fotoVideoWidget->addStyleClass(Bootstrap::Grid::col_full_12);
    fotoVideoWidget->ClickGaleri().connect(this,&Body::initFotoVideoGalery);

    auto iletisimWidget = mMainContainer->addWidget(cpp14::make_unique<IletisimWidget>(this->db()));
    iletisimWidget->addStyleClass(Bootstrap::Grid::col_full_12);

    //    wApp->setInternalPath("");
}

void Body::initKurumsal()
{
    mMainContainer->clear();
    auto w = mMainContainer->addWidget(cpp14::make_unique<KurumsalPage>(this->db()));
    w->addStyleClass(Bootstrap::Grid::col_full_12);
}

void Body::initHaber(std::string mOid)
{

    this->initDirectHaber(mOid);

    wApp->instance()->setInternalPath(u8"col=Haberler&oid="+mOid);

}

void Body::initDirectHaber(const std::string &mOid)
{
    mMainContainer->clear();


//    std::cout << __FILE__ << " " << __LINE__ << " " << __FUNC__ << " : " << mOid << std::endl;

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
                    wApp->setTitle(value + " - @Serik BelediyeSpor");
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


//                _text->setTextFormat(TextFormat::UnsafeXHTML);
                try {
                    auto value = view["html"].get_utf8().value.to_string();
//                    std::cout << "FILE: " << __FILE__ << " Line: " << __LINE__ << value << std::endl;
                    auto _text = _Container->addWidget(cpp14::make_unique<WText>(value , TextFormat::UnsafeXHTML));

//                    std::cout << "Set TEXT: " << _text->setText(value) << std::endl;
//                    _text->setMaximumSize(1024,WLength::Auto);
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

    auto ContentContainer = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    ContentContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    ContentContainer->setContentAlignment(AlignmentFlag::Center);
    ContentContainer->setMargin(20,Side::Top|Side::Bottom);

    auto rContainer = ContentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);
    rContainer->setMaximumSize(1200,WLength::Auto);

    {

        auto titleContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        titleContainer->addStyleClass(Bootstrap::Grid::col_full_12);
        titleContainer->setAttributeValue(Style::style,Style::background::url("img/newsBack.jpg")+Style::background::size::cover+Style::background::position::center_center);
        titleContainer->setHeight(100);

        auto nContainer = titleContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        nContainer->setWidth(WLength("100%"));
        nContainer->setHeight(WLength("100%"));
        nContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));

        auto vLayout = nContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

        auto text = vLayout->addWidget(cpp14::make_unique<WText>("Haberler"),0,AlignmentFlag::Center|AlignmentFlag::Middle);

        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Snow)+Style::font::family::tahoma+Style::font::size::s18px);

    }

    try {
        auto cursor = this->db()->collection("Haberler").find(filter.view(),findOptions);





        for( auto doc : cursor )
        {

            auto _container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_4+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
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
            container->setWidth(WLength("90%"));
            auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
            vLayout->setContentsMargins(15,5,15,5);

            // Resim
            {
                auto imgContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
                imgContainer->setWidth(WLength("100%"));
                imgContainer->setHeight(180);
                imgContainer->addStyleClass(Bootstrap::ImageShape::img_rounded);
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
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::font::family::tahoma+Style::font::weight::bold);
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
    this->initDuyuruList(mOid);

    wApp->instance()->setInternalPath(u8"col=Duyurular&oid="+mOid);
}

void Body::initDirectDuyuru(std::string mOid , WContainerWidget* container )
{

    auto filter = document{};

    try {
        filter.append(kvp("_id",bsoncxx::oid(mOid))) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << "-> filter." << "_id :"<< e.what() << std::endl;
    }


    try {
        auto val = this->db()->collection("Duyurular").find_one(filter.view());


        if( !val ){
            std::cout << "Line: " << __LINE__ << " " << __FILE__ << " " << __FUNCTION__ << " -> No Document Entry";
        }else{

            auto view = val.value().view();

//            auto container = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            container->addStyleClass(Bootstrap::Grid::col_full_12);
            container->setContentAlignment(AlignmentFlag::Center);


            DuyuruItem::DuyuruType tip;


            // Duyuru Tipi
            {
                try {
                    auto value = view["tipi"].get_utf8().value.to_string();

                    if( value == "Duyuru" ) tip = DuyuruItem::DuyuruType::duyuru;
                    if( value == "Musabaka" ) tip = DuyuruItem::DuyuruType::musabaka;

                } catch (bsoncxx::exception &e) {
                    std::string err =  std::string("Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view tipi type is not utf8() :" + std::string(e.what());
                    std::cout << err << std::endl;
                }
            }

            // Başlık Kısmı
            {

                auto _Container = container->addWidget(cpp14::make_unique<WContainerWidget>());
                _Container->setHeight(100);
                _Container->setMaximumSize(1350,WLength::Auto);

                auto imgContainer = _Container->addWidget(cpp14::make_unique<WContainerWidget>());
                imgContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));
                imgContainer->setWidth(WLength("100%"));
                imgContainer->setHeight(WLength("100%"));

            _Container->setAttributeValue(Style::style,Style::background::url("test/3.jpg")
                                                  +Style::background::size::cover
                                                  +Style::background::repeat::norepeat);


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

            if( tip == DuyuruItem::DuyuruType::duyuru )
            {
                auto _Container = container->addWidget(cpp14::make_unique<WContainerWidget>());
                _Container->setHeight(150);
                _Container->setMaximumSize(1350,WLength::Auto);
                _Container->setWidth(WLength("100%"));
                try {
                    auto value = view["icerik"].get_utf8().value.to_string();
                    _Container->addWidget(cpp14::make_unique<WText>(value,TextFormat::UnsafeXHTML));
                } catch (bsoncxx::exception &e) {
                    std::string err =  std::string("Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view icerik type is not utf8() :" + std::string(e.what());
                    std::cout << err << std::endl;
                    _Container->addWidget(cpp14::make_unique<WText>(err));
                }
            }


            if( tip == DuyuruItem::DuyuruType::musabaka )
            {


                auto imgContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());

            imgContainer->setAttributeValue(Style::style,Style::background::url("test/3.jpg")
                                                  +Style::background::size::cover
                                                     +Style::background::repeat::norepeat);

            imgContainer->setPadding(10);

                auto backContianer = imgContainer->addWidget(cpp14::make_unique<WContainerWidget>());

                backContianer->setAttributeValue(Style::style,Style::Border::border("1px solid white")+Style::background::color::rgba(0,0,0,0.7));

                // Takım 1 ve Takım 2
                {

                    auto _Container = backContianer->addWidget(cpp14::make_unique<WContainerWidget>());



                    auto hLayout = _Container->setLayout(cpp14::make_unique<WHBoxLayout>());


                    try {
                        auto value = view["Takim1"].get_utf8().value.to_string();
                        auto text = hLayout->addWidget(cpp14::make_unique<WText>(value),0,AlignmentFlag::Right);
                        text->setAttributeValue(Style::style,Style::font::size::s16px+Style::color::rgb("255,255,255")+Style::font::weight::lighter);

                    } catch (bsoncxx::exception &e) {
                        std::string err =  std::string("Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view Takim1 type is not utf8() :" + std::string(e.what());
                        std::cout << err << std::endl;
                        hLayout->addWidget(cpp14::make_unique<WText>(err),0,AlignmentFlag::Right);
                    }

                    try {
                        auto value = view["Takim2"].get_utf8().value.to_string();
                        auto text = hLayout->addWidget(cpp14::make_unique<WText>(" - "+value),0,AlignmentFlag::Left);
                        text->setAttributeValue(Style::style,Style::font::size::s16px+Style::color::rgb("255,255,255")+Style::font::weight::lighter);
                    } catch (bsoncxx::exception &e) {
                        std::string err =  std::string("Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view Takim2 type is not utf8() :" + std::string(e.what());
                        std::cout << err << std::endl;
                        hLayout->addWidget(cpp14::make_unique<WText>(err),0,AlignmentFlag::Left);
                    }

                    _Container->setMargin(15,Side::Bottom);


                }


                // Yer
                {
                    auto _Container = backContianer->addWidget(cpp14::make_unique<WContainerWidget>());
                    _Container->setMaximumSize(1200,WLength::Auto);
                    _Container->setContentAlignment(AlignmentFlag::Center);

                    try {
                        auto value = view["Yer"].get_utf8().value.to_string();
                        auto text = _Container->addWidget(cpp14::make_unique<WText>(value));
                        text->setAttributeValue(Style::style,Style::font::size::s16px+Style::color::rgb("255,255,255")+Style::font::weight::lighter);
                    } catch (bsoncxx::exception &e) {
                        std::string err =  std::string("Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view Yer type is not utf8() :" + std::string(e.what());
                        std::cout << err << std::endl;
                        _Container->addWidget(cpp14::make_unique<WText>(err));
                    }
                    _Container->setMargin(15,Side::Bottom);
                }


                // Tarih Saat
                {
                    auto _Container = backContianer->addWidget(cpp14::make_unique<WContainerWidget>());
                    _Container->setMaximumSize(1200,WLength::Auto);
                    _Container->setContentAlignment(AlignmentFlag::Center);
                    _Container->setMargin(15,Side::Bottom);

                    try {
                        auto value = view["Tarih"].get_int64().value;
                        auto text = _Container->addWidget(cpp14::make_unique<WText>(QDate::fromString(QString::number(value),"yyyyMMdd").toString("dddd dd/MM/yyyy").toStdString()));
                        text->setAttributeValue(Style::style,Style::font::size::s16px+Style::color::rgb("255,255,255")+Style::font::weight::lighter);
                        text->setMargin(15,Side::Bottom);
                    } catch (bsoncxx::exception &e) {
                        std::string err =  std::string("Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view Tarih type is not get_int64() :" + std::string(e.what());
                        std::cout << err << std::endl;
                        _Container->addWidget(cpp14::make_unique<WText>(err));
                    }

                    _Container->addWidget(cpp14::make_unique<WBreak>());

                    try {
                        auto value = view["Saat"].get_utf8().value.to_string();
                        auto text = _Container->addWidget(cpp14::make_unique<WText>("Saat: "+value));
                        text->setAttributeValue(Style::style,Style::font::size::s16px+Style::color::rgb("255,255,255")+Style::font::weight::lighter);
                    } catch (bsoncxx::exception &e) {
                        std::string err =  std::string("Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view Saat type is not utf8() :" + std::string(e.what());
                        std::cout << err << std::endl;
                        _Container->addWidget(cpp14::make_unique<WText>(err));
                    }

                }

            }


        }



    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
    }

}

void Body::initDuyuruList( std::string mOid )
{

    mMainContainer->clear();



    auto fullContainer = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    fullContainer->addStyleClass(Bootstrap::Grid::col_full_12);

    fullContainer->setMargin(25,Side::Top|Side::Bottom);

    auto fContainer = fullContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    fContainer->addStyleClass(Bootstrap::Grid::container_fluid);
    fContainer->setContentAlignment(AlignmentFlag::Center);

    auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);
    rContainer->setMaximumSize(1200,WLength::Auto);







    auto duyuruDetay = rContainer->addWidget(cpp14::make_unique<DuyuruDetail>(this->db()));
    duyuruDetay->addStyleClass(Bootstrap::Grid::Large::col_lg_9+Bootstrap::Grid::Medium::col_md_8+Bootstrap::Grid::Small::col_sm_8+Bootstrap::Grid::ExtraSmall::col_xs_12);

    if( !mOid.empty() )
    {
        this->initDirectDuyuru(mOid,duyuruDetay);
    }



    auto listContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    listContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_4+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_12);



    try {
        auto cursor = this->db()->collection("Duyurular").find(document{}.view());
        for( auto doc : cursor )
        {
            auto item = listContainer->addWidget(cpp14::make_unique<DuyuruItem>(doc));
            item->ClickDuyuru().connect(this,&Body::initDuyuruList);
        }
    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
    }


}

void Body::initTakimlar(std::string oid)
{

    mMainContainer->clear();

    auto w = mMainContainer->addWidget(cpp14::make_unique<TakimlarPage>(this->db(),oid));
    w->addStyleClass(Bootstrap::Grid::col_full_12);

}

void Body::initFotoVideoGalery()
{
    mMainContainer->clear();
    auto w = mMainContainer->addWidget(cpp14::make_unique<FotoVideoGaleri>(this->db()));
    w->addStyleClass(Bootstrap::Grid::col_full_12);
}

void Body::initHakkinda()
{

    mMainContainer->clear();


    auto filter = document{};




    try {

        auto val = this->db()->collection("Hakkinda").find_one(filter.view());

        if( val )
        {

            auto view = val.value().view();

            auto container = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            container->setContentAlignment(AlignmentFlag::Center);
            container->setMargin(25,Side::Top);

            auto rContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            rContainer->setMaximumSize(1024,WLength::Auto);

            auto text = rContainer->addWidget(cpp14::make_unique<WText>(view["html"].get_utf8().value.to_string(),TextFormat::UnsafeXHTML));

        }

    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
    }



}
