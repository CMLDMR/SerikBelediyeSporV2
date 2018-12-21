#include "taraftaritem.h"

#include <QTextDocument>



TaraftarItem::TaraftarItem(mongocxx::database *_db , bsoncxx::document::view _view)
    :ContainerWidget (_db),mValue(_view)
{

    auto rContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);


    const int height = 110.0;

    // Oyalama Sayısı +OY Sayısı -OY sayısı
    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(height);
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_1+Bootstrap::Grid::Medium::col_md_1+Bootstrap::Grid::Small::col_sm_2+Bootstrap::Grid::ExtraSmall::col_xs_3);
        container->setAttributeValue(Style::style,Style::background::color::rgb(131,98,77)/*+Style::Border::bottom::border("1px solid white")*/);
        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        container->setPadding(0,Side::Top|Side::Top);

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->setContentsMargins(0,0,0,0);
        //        vLayout->addStretch(1);

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("▲"));
            text->setAttributeValue(Style::style,Style::font::size::s18px+Style::font::weight::bold+Style::color::color(Style::color::Green::DarkCyan));
            text->setMargin(0,AllSides);
        }


        {
            int artiOy = 0;
            int eksiOy = 0;
            try {
                auto value = mValue.view()["+oy"].get_int32().value;
                artiOy = value;
            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mValue.view() +oy type is not get_int32() :" + std::string(e.what());
            std::cout << err << std::endl;
            }
            try {
                auto value = mValue.view()["-oy"].get_int32().value;
                eksiOy = value;
            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mValue.view() +oy type is not get_int32() :" + std::string(e.what());
            std::cout << err << std::endl;
            }

            if( artiOy > eksiOy )
            {
                auto text = vLayout->addWidget(cpp14::make_unique<WText>("+"+std::to_string(artiOy-eksiOy)));
                text->setAttributeValue(Style::style,Style::font::size::s18px+Style::font::weight::bold+Style::color::color(Style::color::Green::LawnGreen));
                text->setMargin(0,AllSides);
            }else if (artiOy == eksiOy ) {
                auto text = vLayout->addWidget(cpp14::make_unique<WText>(std::to_string(artiOy-eksiOy)));
                text->setAttributeValue(Style::style,Style::font::size::s18px+Style::font::weight::bold+Style::color::color(Style::color::White::Azure));
                text->setMargin(0,AllSides);
            }else{
                auto text = vLayout->addWidget(cpp14::make_unique<WText>(std::to_string(artiOy-eksiOy)));
                text->setAttributeValue(Style::style,Style::font::size::s18px+Style::font::weight::bold+Style::color::color(Style::color::Red::Red));
                text->setMargin(0,AllSides);
            }


        }


        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("▼"));
            text->setAttributeValue(Style::style,Style::font::size::s18px+Style::font::weight::bold+Style::color::color(Style::color::Orange::DarkOrange));
            text->setMargin(0,AllSides);
        }

    }

    // İçerik
    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(height);
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_11+Bootstrap::Grid::Medium::col_md_11+Bootstrap::Grid::Small::col_sm_10+Bootstrap::Grid::ExtraSmall::col_xs_9);
        container->setAttributeValue(Style::style,Style::background::color::rgb(0,114,118));
        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        {

            try {
                auto value = mValue.view()["baslik"].get_utf8().value.to_string();
                auto text = vLayout->addWidget(cpp14::make_unique<WText>(value,TextFormat::UnsafeXHTML),0,AlignmentFlag::Left|AlignmentFlag::Middle);
                text->setAttributeValue(Style::style,Style::color::rgb("255,255,255")+Style::font::weight::bold);
            } catch (bsoncxx::exception &e) {
                std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mValue.view() baslik type is not utf8() :" + std::string(e.what());
                std::cout << err << std::endl;
                auto text = vLayout->addWidget(cpp14::make_unique<WText>(err,TextFormat::UnsafeXHTML),0,AlignmentFlag::Justify|AlignmentFlag::Middle);
                text->setAttributeValue(Style::style,Style::color::rgb("255,255,255"));
            }
        }

        {

            try {
                auto value = mValue.view()["html"].get_utf8().value.to_string();

                std::unique_ptr<QTextDocument> document = std::make_unique<QTextDocument>();
                document.get()->setHtml(value.c_str());
                value = document.get()->toPlainText().toStdString();

                if( value.size() > 100 )
                {
                    value.resize(100);
                    value.resize(103,'.');
                }
                auto text = vLayout->addWidget(cpp14::make_unique<WText>(value,TextFormat::UnsafeXHTML),0,AlignmentFlag::Right|AlignmentFlag::Middle);
                text->setAttributeValue(Style::style,Style::color::rgb("255,255,255")+Style::font::weight::lighter);
            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mValue.view() baslik type is not utf8() :" + std::string(e.what());
            std::cout << err << std::endl;
            auto text = vLayout->addWidget(cpp14::make_unique<WText>(err,TextFormat::UnsafeXHTML),0,AlignmentFlag::Right|AlignmentFlag::Middle);
            text->setAttributeValue(Style::style,Style::color::rgb("255,255,255"));
            }
        }

        {

            std::string tarih;
            std::string saat;

            try {
                auto value = mValue.view()["julianDate"].get_int64().value;
                tarih = QDate::fromJulianDay(value).toString("dd/MM/yyyy dddd").toStdString();
            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mValue.view() julianDate type is not get_int64() :" + std::string(e.what());
            std::cout << err << std::endl;
            }

            try {
                auto value = mValue.view()["saat"].get_utf8().value.to_string();
                saat = value;
            } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mValue.view() saat type is not utf8() :" + std::string(e.what());
            std::cout << err << std::endl;
            }

            auto text = vLayout->addWidget(cpp14::make_unique<WText>(tarih + " - " + saat),0,AlignmentFlag::Right|AlignmentFlag::Middle);
            text->setAttributeValue(Style::style,Style::color::rgb("255,255,255"));
        }
        vLayout->addStretch(1);
    }


    clicked().connect([=](){
        try {
            auto value = mValue.view()["_id"].get_oid().value.to_string();
            _ClickTaraftarItem.emit(mValue.view()["_id"].get_oid().value.to_string());
        } catch (bsoncxx::exception &e) {
            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in mValue.view() _id type is not get_oid() :" + std::string(e.what());
            std::cout << err << std::endl;
        }
    });

}

Signal<std::string> &TaraftarItem::ClickTaraftarItem()
{

    return _ClickTaraftarItem;

}
