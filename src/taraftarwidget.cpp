#include "taraftarwidget.h"



TaraftarWidget::TaraftarWidget(mongocxx::database *_db)
    : ContainerWidget (_db)
{

    setMargin( 25 , Side::Top|Side::Bottom );

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
    }




    for( int i = 0 ; i < 5 ; i++ )
    {
        auto item = rContainer->addWidget(cpp14::make_unique<TaraftarItem>(this->db()));
        item->addStyleClass(Bootstrap::Grid::col_full_12);
    }




    // Foruma Katıl
    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Center);
//        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);

        auto container_ = container->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Button::Primary);
        container_->setWidth(250);
        container_->setHeight(35);

        auto text = container_->addWidget(cpp14::make_unique<WText>(" Forum'a Katıl "));
        text->setAttributeValue(Style::style,Style::font::size::s20px+Style::font::family::tahoma+Style::font::weight::lighter);
    }





}

TaraftarItem::TaraftarItem(mongocxx::database *_db)
    :ContainerWidget (_db)
{
//    setHeight(50);
//    setAttributeValue(Style::style,Style::Border::border("1px solid gray"));
//    addStyleClass(Bootstrap::ImageShape::img_thumbnail);

    auto fContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    fContainer->addStyleClass(Bootstrap::Grid::container_fluid);

    auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);


    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(80);
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_1+Bootstrap::Grid::Medium::col_md_1+Bootstrap::Grid::Small::col_sm_2+Bootstrap::Grid::ExtraSmall::col_xs_3);
        container->setAttributeValue(Style::style,Style::background::color::rgb(155,208,114)/*+Style::Border::bottom::border("1px solid white")*/);
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
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("+14"));
            text->setAttributeValue(Style::style,Style::font::size::s18px+Style::font::weight::bold+Style::color::color(Style::color::Green::Green));
            text->setMargin(0,AllSides);
        }


        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("▼"));
            text->setAttributeValue(Style::style,Style::font::size::s18px+Style::font::weight::bold+Style::color::color(Style::color::Orange::DarkOrange));
            text->setMargin(0,AllSides);
        }

    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(80);
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_11+Bootstrap::Grid::Medium::col_md_11+Bootstrap::Grid::Small::col_sm_10+Bootstrap::Grid::ExtraSmall::col_xs_9);
        container->setAttributeValue(Style::style,Style::background::color::rgb(114,148,198));
        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Lorem Ipsum, dizgi ve baskı endüstrisinde kullanılan mıgır metinlerdir."
                                                                     " Lorem Ipsum, adı bilinmeyen bir matbaacının bir hurufat numune kitabı oluşturmak üzere..."),0,AlignmentFlag::Justify|AlignmentFlag::Middle);
            text->setAttributeValue(Style::style,Style::color::rgb("255,255,255"));
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("12/10/2023 Çarşamba"),0,AlignmentFlag::Right|AlignmentFlag::Middle);
            text->setAttributeValue(Style::style,Style::color::rgb("255,255,255"));
        }
        vLayout->addStretch(1);
    }


}
