#include "fotovideowidget.h"

FotoVideoWidget::FotoVideoWidget(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    setMargin(75,Side::Top|Side::Bottom);
//    setHeight(550);

    addStyleClass(Bootstrap::Grid::container_fluid);

    auto rContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto _mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        _mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

        auto _rContainer = _mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        _rContainer->addStyleClass(Bootstrap::Grid::row);

        {
            auto _container = _rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
            _container->setContentAlignment(AlignmentFlag::Right);
            auto text = _container->addWidget(cpp14::make_unique<WText>("Fotoğraf"));
            text->setAttributeValue(Style::style,Style::font::size::s36px+Style::font::weight::bold+Style::color::color(Style::color::Orange::Coral));
        }

        {
            auto _container = _rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
            _container->setContentAlignment(AlignmentFlag::Left);
            auto text = _container->addWidget(cpp14::make_unique<WText>("Video"));
            text->setAttributeValue(Style::style,Style::font::size::s36px+Style::font::weight::bold+Style::color::color(Style::color::Green::DarkGreen));
        }
    }


    this->initFotoVideoWidget(rContainer);


    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto _mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        _mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

        auto _rContainer = _mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        _rContainer->addStyleClass(Bootstrap::Grid::row);

        {
            auto _container = _rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);
            _container->setContentAlignment(AlignmentFlag::Center);
            _container->setAttributeValue(Style::style,Style::background::color::rgba(125,125,125));
            auto text = _container->addWidget(cpp14::make_unique<WText>("Tüm Galeri"));
            text->setAttributeValue(Style::style,Style::font::size::s20px+Style::font::weight::lighter+Style::color::color(Style::color::White::Azure));
        }

        container->decorationStyle().setCursor(Cursor::PointingHand);

        container->clicked().connect([=](){
            this->_ClickGaleri.emit(NoClass());
        });


    }
}

Signal<NoClass> &FotoVideoWidget::ClickGaleri()
{
    return _ClickGaleri;
}

void FotoVideoWidget::initFotoVideoWidget(WContainerWidget *rContainer)
{



    auto filter = document{};

    auto sortDoc = document{};



    try {
        sortDoc.append(kvp("_id",-1)) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> sortDoc." << "_id :"<< e.what() << std::endl;
    }

    mongocxx::options::find findOptions;

    findOptions.limit(4);

    findOptions.sort(sortDoc.view());



    try {
        auto cursor = this->db()->collection("Galeri").find(filter.view(),findOptions);


        for( auto doc : cursor )
        {

            std::string iconPath;
            std::string yearNumber;
            std::string oid;


            try {
                auto value = doc["_id"].get_oid().value.to_string();
                oid = value;
            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in doc _id type is not get_oid() :" + std::string(e.what());
            std::cout << err << std::endl;
            }


            try {
                auto value = doc["fotoVideoIcon"].get_oid().value.to_string();
                iconPath = this->downloadFile(value);
            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in doc fotoVideoIcon type is not get_oid() :" + std::string(e.what());
            std::cout << err << std::endl;
            }

            try {
                auto value = doc["year"].get_int32().value;
                yearNumber = std::to_string(value);

            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in doc year type is not get_int32() :" + std::string(e.what());
            std::cout << err << std::endl;
            }


            auto container = rContainer->addWidget(cpp14::make_unique<FotoVideoWidgetItem>(iconPath,yearNumber,oid));
            container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);

        }



    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
    }

}



FotoVideoWidgetItem::FotoVideoWidgetItem(std::string iconPath, std::string year , std::string oid )
{

    auto _mContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    _mContainer->addStyleClass(Bootstrap::Grid::container_fluid+Bootstrap::ImageShape::img_thumbnail);
    _mContainer->setAttributeValue(Style::style,Style::background::url(iconPath)+Style::background::size::cover);
    _mContainer->setHeight(250);
    _mContainer->setMargin(10,Side::Bottom);

    auto vLayout = _mContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

    vLayout->addStretch(1);

    auto _rContainer = _mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    _rContainer->addStyleClass(Bootstrap::Grid::row);
    {
        auto __container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Justify);
        __container->setAttributeValue(Style::style,Style::background::color::rgba(255,255,255,0.90));
        __container->setContentAlignment(AlignmentFlag::Center);
        auto text = __container->addWidget(cpp14::make_unique<WText>(year));
        text->setMargin(WLength::Auto,Side::Left|Side::Right);
        text->setAttributeValue(Style::style,Style::font::size::s16px+Style::font::weight::lighter+Style::font::family::tahoma+Style::color::color(Style::color::Grey::Black));
    }

    clicked().connect([=](){
        auto container = wApp->root()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setPositionScheme(PositionScheme::Fixed);
        container->setContentAlignment(AlignmentFlag::Center);
        container->setAttributeValue(Style::style,container->attributeValue(Style::style)+Style::background::color::rgba(0,0,0,0.7));

        container->setWidth(WLength("100%"));
        container->setHeight(WLength("100%"));
        container->setFloatSide(Side::Top|Side::Left);
        container->setZIndex(1000);
        container->setOffsets(0,Side::Top|Side::Left);



        auto textContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        auto text = textContainer->addWidget(cpp14::make_unique<WText>(year));
        text->setAttributeValue(Style::style,Style::font::size::s28px+Style::color::rgb("255,255,255")+Style::font::family::tahoma+Style::font::weight::lighter);




        auto imgContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());

        imgContainer->setWidth(WLength("100%"));
        imgContainer->setHeight(WLength("100%"));
        imgContainer->setAttributeValue(Style::style,container->attributeValue(Style::style)+Style::background::url(iconPath)+Style::background::size::contain+Style::background::repeat::norepeat+Style::background::position::center_center);
        imgContainer->clicked().connect([=](){
            std::cout << "Remove Widget" << std::endl;
            wApp->root()->removeWidget(container);
        });
    });

}

FotoVideoGaleri::FotoVideoGaleri(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    setMargin(15,Side::Top|Side::Bottom);

    auto fContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    fContainer->addStyleClass(Bootstrap::Grid::container_fluid);

    auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    this->initFotoVideo(rContainer);
}

void FotoVideoGaleri::initFotoVideo(WContainerWidget* rContainer)
{
    auto filter = document{};

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

        auto cursor = this->db()->collection("Galeri").find(filter.view(),findOptions);

        for( auto doc : cursor )
        {

            std::string iconPath;
            std::string yearNumber;
            std::string oid;

            try {
                auto value = doc["_id"].get_oid().value.to_string();
                oid = value;
            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in doc _id type is not get_oid() :" + std::string(e.what());
            std::cout << err << std::endl;
            }


            try {
                auto value = doc["fotoVideoIcon"].get_oid().value.to_string();
                iconPath = this->downloadFile(value);
            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in doc fotoVideoIcon type is not get_oid() :" + std::string(e.what());
            std::cout << err << std::endl;
            }

            try {
                auto value = doc["year"].get_int32().value;
                yearNumber = std::to_string(value);

            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in doc year type is not get_int32() :" + std::string(e.what());
            std::cout << err << std::endl;
            }


            auto container = rContainer->addWidget(cpp14::make_unique<FotoVideoWidgetItem>(iconPath,yearNumber,oid));
            container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);

        }



    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
    }
}
