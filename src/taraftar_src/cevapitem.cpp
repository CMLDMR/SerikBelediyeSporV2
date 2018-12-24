#include "cevapitem.h"



CevapItem::CevapItem(mongocxx::database *_db, bsoncxx::document::view _view)
    : ContainerWidget (_db),mView(_view)
{
    auto rContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);


    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_1+Bootstrap::Grid::Medium::col_md_1+Bootstrap::Grid::Small::col_sm_2+Bootstrap::Grid::ExtraSmall::col_xs_3);
        try {
            auto value = mView["nick"].get_utf8().value.to_string();
            container->addWidget(cpp14::make_unique<WText>(value));
        } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mView nick type is not get_utf8() :" + std::string(e.what());
            std::cout << err << std::endl;
        }
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_1+Bootstrap::Grid::Medium::col_md_1+Bootstrap::Grid::Small::col_sm_2+Bootstrap::Grid::ExtraSmall::col_xs_3);
        try {
            auto value = mView["saat"].get_utf8().value.to_string();
            container->addWidget(cpp14::make_unique<WText>(value));
        } catch (bsoncxx::exception &e) {
        std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mView saat type is not get_utf8() :" + std::string(e.what());
        std::cout << err << std::endl;
        }
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
        try {
            auto value = mView["julianDate"].get_int64().value;
            container->addWidget(cpp14::make_unique<WText>(QDate::fromJulianDay(value).toString("dd/MM/yyyy dddd").toStdString()));
        } catch (bsoncxx::exception &e) {
        std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mView julianDate type is not get_int64() :" + std::string(e.what());
        std::cout << err << std::endl;
        }
    }


    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);
        container->setMargin(25,Side::Top);

        try {
            auto value = mView["yorum"].get_utf8().value.to_string();
            container->addWidget(cpp14::make_unique<WText>(value));
        } catch (bsoncxx::exception &e) {
        std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mView yorum type is not get_utf8() :" + std::string(e.what());
        std::cout << err << std::endl;
        }

    }
}
