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


            auto container = rContainer->addWidget(cpp14::make_unique<FotoVideoWidgetItem>(iconPath,yearNumber));
            container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);

        }



    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
    }

}



FotoVideoWidgetItem::FotoVideoWidgetItem(std::string iconPath, std::string year )
{

    auto _mContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    _mContainer->addStyleClass(Bootstrap::Grid::container_fluid);
    _mContainer->setAttributeValue(Style::style,Style::background::url(iconPath)+Style::background::size::cover);
    _mContainer->setHeight(250);

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
        text->setAttributeValue(Style::style,Style::font::size::s16px+Style::font::weight::bold+Style::color::color(Style::color::Orange::Coral));
    }
}

FotoVideoGaleri::FotoVideoGaleri(mongocxx::database *_db)
    :ContainerWidget (_db)
{

}
