#include "haberduyurucaps.h"

HaberDuyuruCaps::HaberDuyuruCaps(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    setHeight(200);




    {
        auto cContainer = addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        cContainer->setWidth(WLength("70%"));
        cContainer->setHeight(250);
        cContainer->setPositionScheme(PositionScheme::Absolute);
        cContainer->setLeftSide(15.0);
        cContainer->setTopSide(-150);

        {
            auto container = cContainer->addWidget(cpp14::make_unique<HaberDuyuruCapsItem>(this->db(),true));
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_5
                                         +Bootstrap::Grid::Medium::col_md_5
                                     +Bootstrap::Grid::Small::col_sm_5
                                     +Bootstrap::Grid::ExtraSmall::col_xs_12);
                container->setHeight(WLength("100%"));

                this->setHaberOid(container->haberOid());

                container->clicked().connect(this,&HaberDuyuruCaps::emitHaberOid);

        }

        {
            auto container = cContainer->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_2
                                         +Bootstrap::Grid::Medium::col_md_2
                                     +Bootstrap::Grid::Small::col_sm_2
                                     +Bootstrap::Grid::ExtraSmall::col_xs_12);
                container->setHeight(WLength("0%"));
        }

        {
            auto container = cContainer->addWidget(cpp14::make_unique<HaberDuyuruCapsItem>(this->db(),false));
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_5
                                         +Bootstrap::Grid::Medium::col_md_5
                                     +Bootstrap::Grid::Small::col_sm_5
                                     +Bootstrap::Grid::ExtraSmall::col_xs_12);
                container->setHeight(WLength("100%"));
        }

    }



}

Signal<std::string> &HaberDuyuruCaps::ClickHaber()
{

    return _ClickHaber;

}

void HaberDuyuruCaps::emitHaberOid()
{

    this->_ClickHaber.emit(this->haberOid());

}

std::string HaberDuyuruCaps::haberOid() const
{
    return mHaberOid;
}

void HaberDuyuruCaps::setHaberOid(const std::string &haberOid)
{
    mHaberOid = haberOid;
}

HaberDuyuruCapsItem::HaberDuyuruCapsItem(mongocxx::database *_db, bool m_Haber)
    :ContainerWidget (_db)
{
    if( m_Haber )
    {
        this->loadHaber();
    }else{
        setBackGroundImage("test/2.jpg");
        this->loadDuyuru();
    }



}

void HaberDuyuruCapsItem::loadHaber()
{
    bool m_Haber = true;
    auto filter = document{};


    try {
        filter.append(kvp("yayinda",true)) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << "-> filter." << "yayinda :"<< e.what() << std::endl;
    }


    auto sortDoc = document{};

    try {
        sortDoc.append(kvp("_id",-1)) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << "-> sortDoc." << "_id :"<< e.what() << std::endl;
    }


    mongocxx::options::find findOptions;

    findOptions.limit(1);
    findOptions.skip(5);

    findOptions.sort(sortDoc.view());



    try {
        auto val = this->db()->collection("Haberler").find_one(filter.view(),findOptions);
        if( val )
        {

            auto view = val.value().view();

            try {
                auto value = view["habericon"].get_oid().value.to_string();
                this->setBackGroundImg(this->downloadFile(value));
                this->setBackGroundImage(this->backGroundImg());

            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << "->in view habericon type is not " << "get_oid() :"<< e.what() << std::endl;
            }


            try {
                auto value = view["baslik"].get_utf8().value.to_string();
                this->setHaberTitle(value);
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << "->in view baslik type is not " << "get_utf8() :"<< e.what() << std::endl;
            }


            try {
                auto value = view["_id"].get_oid().value.to_string();
                this->setHaberOid(value);
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << "->in view _id type is not " << "Oid :"<< e.what() << std::endl;
            }

        }else{

        }
    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
    }



    auto container = addWidget(cpp14::make_unique<WContainerWidget>());
    container->setWidth(WLength("100%"));
    container->setHeight(WLength("100%"));
    container->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0,0.7));

    auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

    vLayout->addStretch(1);
    auto haberTitle = vLayout->addWidget(cpp14::make_unique<WText>("Haber"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
    haberTitle->setAttributeValue(Style::style,Style::font::size::s20px+Style::color::color(Style::color::White::White));

    vLayout->addStretch(1);

    auto ContentTitle = vLayout->addWidget(cpp14::make_unique<WText>(this->haberTitle()),0,AlignmentFlag::Center|AlignmentFlag::Middle);
    ContentTitle->setAttributeValue(Style::style,Style::font::size::s24px
                                        +Style::font::weight::bold
                                        +Style::color::color(Style::color::Orange::DarkOrange));
    vLayout->addStretch(1);

    {
        auto _Container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        _Container->decorationStyle().setBorder(WBorder(BorderStyle::Solid,2,WColor(255,255,255)));
        _Container->setPadding(10,AllSides);
        _Container->setPadding(25,Side::Right|Side::Left);
        auto DetayTitle = _Container->addWidget(cpp14::make_unique<WText>("Detay"));
        DetayTitle->setAttributeValue(Style::style,Style::font::size::s18px
                                          +Style::font::weight::lighter
                                          +Style::color::color(Style::color::White::AliceBlue));
    }
    vLayout->addStretch(1);
}

void HaberDuyuruCapsItem::loadDuyuru()
{

    bool m_Haber = false;
    auto filter = document{};


    try {
        filter.append(kvp("yayinda",bsoncxx::types::b_utf8{"Yayında"})) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << "-> filter." << "yayinda :"<< e.what() << std::endl;
    }


    auto sortDoc = document{};

    try {
        sortDoc.append(kvp("_id",-1)) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << "-> sortDoc." << "_id :"<< e.what() << std::endl;
    }


    mongocxx::options::find findOptions;

    findOptions.limit(1);
//    findOptions.skip(5);

    findOptions.sort(sortDoc.view());



    try {
        auto val = this->db()->collection("Duyurular").find_one(filter.view(),findOptions);
        if( val )
        {

            auto view = val.value().view();

//            try {
//                auto value = view["habericon"].get_oid().value.to_string();
//                this->setBackGroundImg(this->downloadFile(value));
//                this->setBackGroundImage(this->backGroundImg());

//            } catch (bsoncxx::exception &e) {
//                std::cout << "Line " << __LINE__ << "->in view habericon type is not " << "get_oid() :"<< e.what() << std::endl;
//            }


            try {
                auto value = view["tipi"].get_utf8().value.to_string();
                this->setDuyuruTipi(value);
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << "->in view baslik type is not " << "get_utf8() :"<< e.what() << std::endl;
            }


            try {
                auto value = view["baslik"].get_utf8().value.to_string();
                this->setDuyuruBaslik(value);
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << "->in view baslik type is not " << "get_utf8() :"<< e.what() << std::endl;
            }


            try {
                auto value = view["_id"].get_oid().value.to_string();
                this->setDuyuruOid(value);
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << "->in view _id type is not " << "Oid :"<< e.what() << std::endl;
            }

        }else{

        }
    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
    }



    auto container = addWidget(cpp14::make_unique<WContainerWidget>());
    container->setWidth(WLength("100%"));
    container->setHeight(WLength("100%"));
    container->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0,0.7));

    auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

    vLayout->addStretch(1);
    auto haberTitle = vLayout->addWidget(cpp14::make_unique<WText>(this->duyuruTipi()),0,AlignmentFlag::Center|AlignmentFlag::Middle);
    haberTitle->setAttributeValue(Style::style,Style::font::size::s20px+Style::color::color(Style::color::White::White));

    vLayout->addStretch(1);

    auto ContentTitle = vLayout->addWidget(cpp14::make_unique<WText>(this->duyuruBaslik()),0,AlignmentFlag::Center|AlignmentFlag::Middle);
    ContentTitle->setAttributeValue(Style::style,Style::font::size::s24px
                                        +Style::font::weight::bold
                                        +Style::color::color(Style::color::Orange::DarkOrange));
    vLayout->addStretch(1);

    {
        auto _Container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        _Container->decorationStyle().setBorder(WBorder(BorderStyle::Solid,2,WColor(255,255,255)));
        _Container->setPadding(10,AllSides);
        _Container->setPadding(25,Side::Right|Side::Left);
        auto DetayTitle = _Container->addWidget(cpp14::make_unique<WText>("Detay"));
        DetayTitle->setAttributeValue(Style::style,Style::font::size::s18px
                                          +Style::font::weight::lighter
                                          +Style::color::color(Style::color::White::AliceBlue));
    }
    vLayout->addStretch(1);

}

std::string HaberDuyuruCapsItem::duyuruOid() const
{
    return mDuyuruOid;
}

void HaberDuyuruCapsItem::setDuyuruOid(const std::string &duyuruOid)
{
    mDuyuruOid = duyuruOid;
}

std::string HaberDuyuruCapsItem::duyuruBaslik() const
{
    return mDuyuruBaslik;
}

void HaberDuyuruCapsItem::setDuyuruBaslik(const std::string &duyuruBaslik)
{
    mDuyuruBaslik = duyuruBaslik;
}

std::string HaberDuyuruCapsItem::duyuruTipi() const
{
    return mDuyuruTipi;
}

void HaberDuyuruCapsItem::setDuyuruTipi(const std::string &duyuruTipi)
{
    mDuyuruTipi = duyuruTipi;
}

std::string HaberDuyuruCapsItem::haberOid() const
{
    return mHaberOid;
}

void HaberDuyuruCapsItem::setHaberOid(const std::string &haberOid)
{
    mHaberOid = haberOid;
}

std::string HaberDuyuruCapsItem::backGroundImg() const
{
    return mBackGroundImg;
}

void HaberDuyuruCapsItem::setBackGroundImg(const std::string &backGroundImg)
{
    mBackGroundImg = backGroundImg;
}

std::string HaberDuyuruCapsItem::haberTitle() const
{
    return mHaberTitle;
}

void HaberDuyuruCapsItem::setHaberTitle(const std::string &haberTitle)
{
    mHaberTitle = haberTitle;
}



