#include "iletisimwidget.h"

IletisimWidget::IletisimWidget(mongocxx::database *_db)
    :ContainerWidget (_db)
{


    setMargin(150,Side::Top);

    auto fContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    fContainer->addStyleClass(Bootstrap::Grid::container_fluid);
    fContainer->setAttributeValue(Style::style,Style::background::color::rgb(0,0,0));
    fContainer->setContentAlignment(AlignmentFlag::Center);

    auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    rContainer->setMaximumSize(1440 , WLength::Auto );

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_4
                                 +Bootstrap::Grid::Medium::col_md_4
                                 +Bootstrap::Grid::Small::col_sm_6
                                 +Bootstrap::Grid::ExtraSmall::col_xs_12);



        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

        vLayout->addStretch(1);

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Spor Okulları"));
            text->setAttributeValue(Style::style,Style::font::weight::bold
                                        +Style::font::size::s18px
                                        +Style::color::color(Style::color::White::Snow));
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Futbol"));
            text->setAttributeValue(Style::style,Style::font::weight::normal
                                        +Style::font::size::s14px
                                        +Style::color::color(Style::color::White::Snow));
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Golf"));
            text->setAttributeValue(Style::style,Style::font::weight::normal
                                        +Style::font::size::s14px
                                        +Style::color::color(Style::color::White::Snow));
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Bisiklet"));
            text->setAttributeValue(Style::style,Style::font::weight::normal
                                        +Style::font::size::s14px
                                        +Style::color::color(Style::color::White::Snow));
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Yüzme"));
            text->setAttributeValue(Style::style,Style::font::weight::normal
                                        +Style::font::size::s14px
                                        +Style::color::color(Style::color::White::Snow));
        }

        vLayout->addStretch(1);



    }


    {
        auto _container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        _container->addStyleClass(Bootstrap::Grid::Large::col_lg_4
                                 +Bootstrap::Grid::Medium::col_md_4
                                 +Bootstrap::Grid::Small::col_sm_6
                                 +Bootstrap::Grid::ExtraSmall::col_xs_12);

        _container->setHeight(350);
        _container->setAttributeValue(Style::style,Style::background::color::rgb(255,255,255));

        {
            auto container_ = _container->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
            container_->setHeight(10);
            container_->setAttributeValue(Style::style,Style::background::color::rgb(15+20,48+20,25+20));
            container_->setMargin(-100,Side::Top);
            container_->setMargin(-15,Side::Left|Side::Right);
        }

        auto container = _container->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));


        container->setWidth(WLength("100%"));
        container->setHeight(WLength("120%"));
        container->setBottomSide(0);
        container->setMargin(-50,Side::Top);

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

//        vLayout->addStretch(1);

        {
            auto imgContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center);
            imgContainer->setWidth(150);
            imgContainer->setHeight(150);
            imgContainer->setAttributeValue(Style::style,Style::background::url("img/logo.png")
                                             +Style::background::repeat::norepeat
                                             +Style::background::position::center_center
                                             +Style::background::size::contain);
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Serik BelediyeSpor"));
            text->setAttributeValue(Style::style,Style::font::weight::bold
                                        +Style::font::size::s18px
                                        +Style::color::color(Style::color::Grey::Black));
        }

//        {
//            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Futbol"));
//            text->setAttributeValue(Style::style,Style::font::weight::normal
//                                        +Style::font::size::s14px
//                                        +Style::color::color(Style::color::Grey::Black));
//        }

//        {
//            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Golf"));
//            text->setAttributeValue(Style::style,Style::font::weight::normal
//                                        +Style::font::size::s14px
//                                        +Style::color::color(Style::color::Grey::Black));
//        }

//        {
//            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Hentbol"));
//            text->setAttributeValue(Style::style,Style::font::weight::normal
//                                        +Style::font::size::s14px
//                                        +Style::color::color(Style::color::Grey::Black));
//        }

//        {
//            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Yüzme"));
//            text->setAttributeValue(Style::style,Style::font::weight::normal
//                                        +Style::font::size::s14px
//                                        +Style::color::color(Style::color::Grey::Black));
//        }


        vLayout->addStretch(1);



    }





    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_4
                                 +Bootstrap::Grid::Medium::col_md_4
                                 +Bootstrap::Grid::Small::col_sm_12
                                 +Bootstrap::Grid::ExtraSmall::col_xs_12);


        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

        vLayout->addStretch(1);

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Adres"));
            text->setAttributeValue(Style::style,Style::font::weight::bold
                                        +Style::font::size::s14px
                                        +Style::color::color(Style::color::White::Snow));
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("Serik / Antalya / Türkiye"));
            text->setAttributeValue(Style::style,Style::font::weight::normal
                                        +Style::font::size::s14px
                                        +Style::color::color(Style::color::White::Snow));
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("e-Mail"));
            text->setAttributeValue(Style::style,Style::font::weight::bold
                                        +Style::font::size::s18px
                                        +Style::color::color(Style::color::White::Snow));
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("info@serikbelediyespor.com"));
            text->setAttributeValue(Style::style,Style::font::weight::normal
                                        +Style::font::size::s14px
                                        +Style::color::color(Style::color::White::Snow));
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("İletişim"));
            text->setAttributeValue(Style::style,Style::font::weight::bold
                                        +Style::font::size::s14px
                                        +Style::color::color(Style::color::White::Snow));
        }

        {
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("0 242 722 22 22"));
            text->setAttributeValue(Style::style,Style::font::weight::normal
                                        +Style::font::size::s14px
                                        +Style::color::color(Style::color::White::Snow));
        }

        vLayout->addStretch(1);





    }

}
