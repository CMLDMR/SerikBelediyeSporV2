#include "haberduyurucaps.h"

HaberDuyuruCaps::HaberDuyuruCaps(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    setHeight(150);
    addStyleClass("HaberDuyuruContainer");




    {
        auto cContainer = addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        cContainer->setWidth(WLength("70%"));
        cContainer->setHeight(250);
        cContainer->setPositionScheme(PositionScheme::Absolute);
        cContainer->setLeftSide(15.0);
        cContainer->setTopSide(-150);
        cContainer->addStyleClass("HaberDuyuruCaps");

        {
            auto container = cContainer->addWidget(cpp14::make_unique<HaberDuyuruCapsItem>(this->db(),true));
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_5
                                         +Bootstrap::Grid::Medium::col_md_5
                                     +Bootstrap::Grid::Small::col_sm_6
                                     +Bootstrap::Grid::ExtraSmall::col_xs_6);
                container->setHeight(WLength("100%"));

                this->setHaberOid(container->haberOid());

                container->clicked().connect(this,&HaberDuyuruCaps::emitHaberOid);

        }

        {
            auto container = cContainer->addWidget(cpp14::make_unique<HaberDuyuruCapsItem>(this->db(),false));
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_5
                                         +Bootstrap::Grid::Medium::col_md_5
                                     +Bootstrap::Grid::Small::col_sm_6
                                     +Bootstrap::Grid::ExtraSmall::col_xs_6
                                     +Bootstrap::Grid::Offset::Large::col_lg_2
                                     +Bootstrap::Grid::Offset::Medium::col_md_2);
                container->setHeight(WLength("100%"));
                this->setDuyuruOid(container->duyuruOid());
                container->clicked().connect(this,&HaberDuyuruCaps::emitDuyuruOid);
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

void HaberDuyuruCaps::emitDuyuruOid()
{
    std::cout << __LINE__ << " " << __FUNCTION__ << " " << this->duyuruOid() << std::endl;
    this->_ClickDuyuru.emit(this->duyuruOid());
}

std::string HaberDuyuruCaps::duyuruOid() const
{
    return mDuyuruOid;
}

void HaberDuyuruCaps::setDuyuruOid(const std::string &duyuruOid)
{
    mDuyuruOid = duyuruOid;
}

Signal<std::string> &HaberDuyuruCaps::ClickDuyuru()
{
    return _ClickDuyuru;
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
        setBackGroundImage("test/1.jpg");
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
    haberTitle->addStyleClass("haberTextCss");

    vLayout->addStretch(1);

    auto ContentTitle = vLayout->addWidget(cpp14::make_unique<WText>(this->haberTitle()),0,AlignmentFlag::Center|AlignmentFlag::Middle);
    ContentTitle->setAttributeValue(Style::style,Style::font::size::s24px
                                        +Style::font::weight::bold
                                        +Style::color::color(Style::color::Orange::DarkOrange));
    ContentTitle->addStyleClass("HaberTitleCss");
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
        DetayTitle->addStyleClass("haberTextCss");

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
    haberTitle->addStyleClass("haberTextCss");

    vLayout->addStretch(1);

    auto ContentTitle = vLayout->addWidget(cpp14::make_unique<WText>(this->duyuruBaslik()),0,AlignmentFlag::Center|AlignmentFlag::Middle);
    ContentTitle->setAttributeValue(Style::style,Style::font::size::s24px
                                        +Style::font::weight::bold
                                        +Style::color::color(Style::color::Purple::MediumSlateBlue));
    ContentTitle->addStyleClass("HaberTitleCss");
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
        DetayTitle->addStyleClass("haberTextCss");
    }
    vLayout->addStretch(1);

}

std::string HaberDuyuruCapsItem::duyuruOid() const
{
    return mDuyuruOid;
}

void HaberDuyuruCapsItem::setDuyuruOid(const std::string &duyuruOid)
{
    std::cout << __LINE__ << " " << __FUNCTION__ << " " << duyuruOid << std::endl;
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




DuyuruItem::DuyuruItem(bsoncxx::document::view &view_)
    :view (view_)
{


    addStyleClass(Bootstrap::ImageShape::img_thumbnail);
    setMargin(5,Side::Bottom);
    decorationStyle().setCursor(Cursor::PointingHand);

    auto vLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    try {

        auto value = view["tipi"].get_utf8().value.to_string();

        vLayout->addWidget(cpp14::make_unique<WText>(value),0,AlignmentFlag::Center);

        if( value == "Duyuru" ) setType( DuyuruType::duyuru );

        if( value == "Musabaka" ) setType( DuyuruType::musabaka );

    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "->in view tipi type is not " << "get_utf8() :"<< e.what() << std::endl;
    }


    if( this->type() == DuyuruType::duyuru )
    {
        try {
            auto value = view["baslik"].get_utf8().value.to_string();
            auto item = vLayout->addWidget(cpp14::make_unique<WText>(value));
        } catch (bsoncxx::exception &e) {
            std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "->in view baslik type is not " << "get_utf8() :"<< e.what() << std::endl;
        }

        try {
            auto value = view["_id"].get_oid().value.to_string();
            this->setOid(value);
        } catch (bsoncxx::exception &e) {
        std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view _şd type is not get_oid() :" + std::string(e.what());
        std::cout << err << std::endl;
        }

        setAttributeValue(Style::style,Style::background::color::color("#CCEEFF"));
    }else if ( this->type() == DuyuruType::musabaka ) {
        setAttributeValue(Style::style,Style::background::color::color("#CCFFDD"));

        try {
            auto value = view["baslik"].get_utf8().value.to_string();
            auto item = vLayout->addWidget(cpp14::make_unique<WText>(value));
        } catch (bsoncxx::exception &e) {
            std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "->in view baslik type is not " << "get_utf8() :"<< e.what() << std::endl;
        }



        auto container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());

        auto hLayout = container->setLayout(cpp14::make_unique<WHBoxLayout>());

        try {
            auto value = view["Takim1"].get_utf8().value.to_string();
            hLayout->addWidget(cpp14::make_unique<WText>(value+" "),0,AlignmentFlag::Right);
        } catch (bsoncxx::exception &e) {
            std::string err =  std::string("Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view Takim1 type is not utf8() :" + std::string(e.what());
            std::cout << err << std::endl;
            hLayout->addWidget(cpp14::make_unique<WText>(err));
        }


        try {
            auto value = view["Takim2"].get_utf8().value.to_string();
            hLayout->addWidget(cpp14::make_unique<WText>("- "+value),0,AlignmentFlag::Left);
        } catch (bsoncxx::exception &e) {
            std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "->in view Takim2 type is not " << "get_utf8() :"<< e.what() << std::endl;
        }


        try {
            auto value = view["_id"].get_oid().value.to_string();
            this->setOid(value);
        } catch (bsoncxx::exception &e) {
        std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view _şd type is not get_oid() :" + std::string(e.what());
        std::cout << err << std::endl;
        }

    }




    this->clicked().connect([=](){
        this->_ClickDuyuru.emit(this->oid());
    });





}

DuyuruItem::DuyuruType DuyuruItem::type() const
{
    return mType;
}

void DuyuruItem::setType(const DuyuruType &type)
{
    mType = type;
}

Signal<std::string> &DuyuruItem::ClickDuyuru()
{
    return _ClickDuyuru;
}

std::string DuyuruItem::oid() const
{
    return mOid;
}

void DuyuruItem::setOid(const std::string &oid)
{
    mOid = oid;
}




DuyuruDetail::DuyuruDetail(mongocxx::database *_db)
    :ContainerWidget (_db)
{

}

std::string DuyuruDetail::oid() const
{
    return mOid;
}

void DuyuruDetail::setOid(const std::string &oid)
{
    mOid = oid;
}
