#include "takimlarwidget.h"

TakimlarWidget::TakimlarWidget(mongocxx::database *_db)
    :ContainerWidget (_db)
{

//    const int _height = 550;
    setAttributeValue(Style::style,Style::background::url("test/3.jpg")
                          +Style::background::size::cover
                          +Style::background::repeat::norepeat
                          +Style::background::position::center_center);

    auto mContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    mContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,25,0,0.75));
    mContainer->addStyleClass(Bootstrap::Grid::container_fluid);
    mContainer->setContentAlignment(AlignmentFlag::Center|AlignmentFlag::Middle);

    auto rContainer = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);
    rContainer->setMaximumSize(1024,WLength::Auto);
    rContainer->setPadding(65,Side::Top|Side::Bottom);

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto text = container->addWidget(cpp14::make_unique<WText>("Takımlarımız"));
        text->setAttributeValue(Style::style,Style::color::color(Style::color::Orange::OrangeRed)+Style::font::size::s36px+Style::font::weight::bold);
    }


    {

        auto filter = document{};

        auto project = document{};

        try {
            project.append(kvp("Baslik",true)) ;
        } catch (bsoncxx::exception &e) {
            std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> project." << "baslik :"<< e.what() << std::endl;
        }

        try {
            project.append(kvp("icon",true)) ;
        } catch (bsoncxx::exception &e) {
            std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> project." << "icon :"<< e.what() << std::endl;
        }

        mongocxx::options::find findOptions;

        findOptions.limit(6);
        findOptions.projection(project.view());

        try {
            auto cursor = this->db()->collection("Kategoriler").find(filter.view(),findOptions);

            for( auto doc : cursor )
            {

                std::string oid;
                std::string backUrl;
                std::string mTitle;

                try {
                    auto value = doc["_id"].get_oid().value.to_string();
                    oid = value;
                } catch (bsoncxx::exception &e) {
                std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in doc _id type is not oid() :" + std::string(e.what());
                std::cout << err << std::endl;
                }

                try {
                    auto value = doc["Baslik"].get_utf8().value.to_string();
                    mTitle = value;
                } catch (bsoncxx::exception &e) {
                std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in doc Baslik type is not get_utf8() :" + std::string(e.what());
                std::cout << err << std::endl;
                }

                try {
                    auto value = doc["icon"].get_oid().value.to_string();
                    backUrl = this->downloadFile(value);
                } catch (bsoncxx::exception &e) {
                std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in doc icon type is not get_oid() :" + std::string(e.what());
                std::cout << err << std::endl;
                }

                this->addTakim(oid,mTitle,backUrl,rContainer);

            }

        } catch (mongocxx::exception &e) {
            std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
        }

    }


    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->decorationStyle().setCursor(Cursor::PointingHand);

        auto text = container->addWidget(cpp14::make_unique<WText>("Tüm Takımlar"));
        text->setAttributeValue(Style::style,Style::color::color(Style::color::Orange::DarkOrange)+Style::font::size::s20px+Style::font::weight::lighter+Style::font::family::tahoma);
    }

}

Signal<std::string> &TakimlarWidget::ClickTakim()
{

    return _ClickTakim;

}

void TakimlarWidget::addTakim(const std::string &oid, const std::string &takimadi, const std::string &backurl, WContainerWidget *rContainer)
{
    auto container = rContainer->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
    container->addStyleClass(Bootstrap::Grid::Large::col_lg_4);
    auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
    vLayout->addStretch(1);
    {
        auto _container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
        _container->setHeight(WLength("100%"));
        auto imgContainer = _container->addWidget(cpp14::make_unique<WContainerWidget>());
        imgContainer->setHeight(175);
        imgContainer->decorationStyle().setBorder(WBorder(BorderStyle::Solid,1,WColor(255,255,255)));
        imgContainer->setAttributeValue(Style::style,Style::background::url(backurl)+Style::background::size::cover);
        imgContainer->decorationStyle().setCursor(Cursor::PointingHand);
        imgContainer->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        imgContainer->setWidth(WLength("100%"));


        auto colorContainer = imgContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        colorContainer->setWidth(WLength("100%"));
        colorContainer->setHeight(WLength("100%"));
        colorContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));

        auto _vLayout = colorContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
        _vLayout->addStretch(1);

        auto text = _vLayout->addWidget(cpp14::make_unique<WText>(takimadi));
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Linen)+Style::font::size::s20px+Style::font::weight::lighter);

        _vLayout->addStretch(1);


    }
    vLayout->addStretch(1);

    container->clicked().connect([=](){
        this->_ClickTakim.emit(oid);
    });
}

TakimlarPage::TakimlarPage(mongocxx::database *_db, const std::string &takimOid)
    :ContainerWidget (_db),mCurrentTakimValue(document{}.view())
{

    if( !takimOid.empty() )
    {
        this->initTakim(takimOid);
    }
}

void TakimlarPage::initTakim(std::string takimoid)
{

    clear();


    auto fContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    fContainer->addStyleClass(Bootstrap::Grid::container_fluid);
    fContainer->setContentAlignment(AlignmentFlag::Center);

    auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);
    rContainer->setMaximumSize(1400,WLength::Auto);







    auto filter = document{};


    try {
        filter.append(kvp("_id",bsoncxx::oid{takimoid})) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> filter." << "_id :"<< e.what() << std::endl;
    }


    std::string takimadi;
    std::string takimBackUrl;
    std::vector<std::string> menuList;


    try {

        auto val = this->db()->collection("Kategoriler").find_one(filter.view());

        if( val )
        {
            auto view = val.value().view();

            this->mCurrentTakimValue = bsoncxx::document::value(view);

            try {
                auto value = view["Baslik"].get_utf8().value.to_string();

                takimadi = value;

            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view Baslik type is not get_utf8() :" + std::string(e.what());
            std::cout << err << std::endl;
            takimadi = err;
            }


            try {
                auto value = this->mCurrentTakimValue.view()["icon"].get_oid().value.to_string();
                takimBackUrl = this->downloadFile(value);
            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view icon type is not get_oid() :" + std::string(e.what());
            std::cout << err << std::endl;
            takimBackUrl = this->getErroImgPath();
            }


            for( auto menuItem = this->mCurrentTakimValue.view().begin() ; menuItem != this->mCurrentTakimValue.view().end() ; menuItem++ ){
                if( menuItem->key().to_string() != "Baslik" && menuItem->key().to_string() != "_id" && menuItem->key().to_string() != "icon" )
                {
                    menuList.push_back(menuItem->key().to_string());
                }
            }


        }

    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
    }


    // Kategori Başlığı
    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(75);
        container->setAttributeValue(Style::style,Style::background::url(takimBackUrl)+Style::background::size::cover+Style::background::repeat::norepeat);
        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail+Bootstrap::Grid::col_full_12);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

        auto text = vLayout->addWidget(cpp14::make_unique<WText>(takimadi),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Snow)+Style::font::family::tahoma+Style::font::weight::lighter+Style::font::size::s20px);

    }


    // Menü Listesi
    {

        auto mContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        mContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_3+Bootstrap::Grid::ExtraSmall::col_xs_12);


        auto vLayout = mContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

        for( auto item : menuList )
        {
            auto container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
            container->setMargin(5,Side::Top|Side::Bottom);
            container->setHeight(30);
            container->addStyleClass(Bootstrap::ImageShape::img_rounded);
            container->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));
            container->decorationStyle().setCursor(Cursor::PointingHand);
            container->clicked().connect([=](){this->initMenuContent(item);});
            auto vLayout_ = container->setLayout(cpp14::make_unique<WVBoxLayout>());
            auto text = vLayout_->addWidget(cpp14::make_unique<WText>(item),0,AlignmentFlag::Center|AlignmentFlag::Middle);
            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Snow)+Style::font::family::tahoma+Style::font::weight::lighter+Style::font::size::s16px);
        }

        vLayout->addStretch(1);

    }

    //  İçerik
    {
        mIcerikContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        mIcerikContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_10+Bootstrap::Grid::Medium::col_md_10+Bootstrap::Grid::Small::col_sm_9+Bootstrap::Grid::ExtraSmall::col_xs_12);

    }




}

void TakimlarPage::initMenuContent(const std::string &menu)
{
    mIcerikContainer->clear();
    auto container = mIcerikContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    container->setWidth(WLength("100%"));

    std::cout << "Current TakimView: " << menu << std::endl;
    std::cout << bsoncxx::to_json(this->currentTakimView()) << std::endl;
    std::cout << "Endline" << std::endl;
    bsoncxx::document::view view;

    try {
        auto value = this->mCurrentTakimValue.view()[menu].get_document().value;
        view = value;
    } catch (bsoncxx::exception &e) {
    std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in this->currentTakimView() menu type is not type :" + std::string(e.what());
    std::cout << err << std::endl;
    auto text = container->addWidget(cpp14::make_unique<WText>(err,TextFormat::UnsafeXHTML));

    }





    try {
        auto value = view["files"].get_array().value;
        for( auto oiditem : value )
        {
            this->downloadFile(oiditem.get_oid().value.to_string(),true);
        }
    } catch (bsoncxx::exception &e) {
    std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view files type is not get_array() :" + std::string(e.what());
    std::cout << err << std::endl;
    auto text = container->addWidget(cpp14::make_unique<WText>(err,TextFormat::UnsafeXHTML));
    }


    try {
        auto value = view["html"].get_utf8().value.to_string();
        auto text = container->addWidget(cpp14::make_unique<WText>(value,TextFormat::UnsafeXHTML));
    } catch (bsoncxx::exception &e) {
    std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in view html type is not get_utf8() :" + std::string(e.what());
    std::cout << err << std::endl;
    auto text = container->addWidget(cpp14::make_unique<WText>(err,TextFormat::UnsafeXHTML));
    }





}

bsoncxx::document::view TakimlarPage::currentTakimView() const
{
    return mCurrentTakimValue.view();
}

//void TakimlarPage::setCurrentTakimView(const bsoncxx::document::view &currentTakimView)
//{
//    mCurrentTakimView = currentTakimView;

//    for( auto item : mCurrentTakimView )
//    {
//        std::cout << "KEY: " << item.key().to_string() << std::endl;
//    }
//}
