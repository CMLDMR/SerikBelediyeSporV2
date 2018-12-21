#include "taraftarwidget.h"

#include "body.h"
#include "taraftar_src/yenikonu.h"
#include "taraftar_src/taraftaritem.h"

TaraftarWidget::TaraftarWidget(mongocxx::database *_db, const int &limit, const int &skip)
    : ContainerWidget (_db)
{

    setMargin( 25 , Side::Top );
    setMargin( 50 , Side::Bottom );

    auto fContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    fContainer->addStyleClass(Bootstrap::Grid::container_fluid);
    fContainer->setContentAlignment(AlignmentFlag::Center);
//    fContainer->setMaximumSize(1250,WLength::Auto);


    auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row/*+Bootstrap::ImageShape::img_thumbnail*/);
    rContainer->setMaximumSize(1250,WLength::Auto);

//    rContainer->setMargin(50,Side::Top|Side::Bottom);


    // Title
    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Center);

        auto text = container->addWidget(cpp14::make_unique<WText>(" Forum "));
        text->setAttributeValue(Style::style,Style::font::size::s24px+Style::font::family::tahoma+Style::font::weight::lighter);
        container->decorationStyle().setCursor(Cursor::PointingHand);
        container->clicked().connect([=](){_ClickTaraftar.emit(NoClass());});
    }


    auto filter = document{};

    // TODO: Kullanımda Açılacak. Deneme Amaaçlı Kapalı
    //        try {
    //            filter.append(kvp("onay",true)) ;
    //        } catch (bsoncxx::exception &e) {
    //            std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> filter." << "onay :"<< e.what() << std::endl;
    //        }


    mongocxx::options::find findOptions;


    auto sortDoc = document{};

    try {
        sortDoc.append(kvp("updated",-1)) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> sortDoc." << "updated :"<< e.what() << std::endl;
    }


    findOptions.sort(sortDoc.view());





    try {
        auto cursor = this->db()->collection("forum").find(filter.view(),findOptions);

        for( auto doc : cursor )
        {
            auto item = rContainer->addWidget(cpp14::make_unique<TaraftarItem>(this->db(),doc));
            item->addStyleClass(Bootstrap::Grid::container_fluid);
        }

    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
    }

}

Signal<NoClass> &TaraftarWidget::ClickTaraftar()
{
    return _ClickTaraftar;
}




