#include "takimlarwidget.h"

TakimlarWidget::TakimlarWidget(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    const int _height = 550;
//    setHeight(_height);
    setAttributeValue(Style::style,Style::background::url("test/3.jpg")
                          +Style::background::size::cover
                          +Style::background::repeat::norepeat
                          +Style::background::position::center_center);


    auto mContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    mContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,25,0,0.75));
//    mContainer->setHeight(_height);
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
        auto container = rContainer->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_4);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        {
            auto _container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->setHeight(WLength("40%"));
            auto imgContainer = _container->addWidget(cpp14::make_unique<WContainerWidget>());
            imgContainer->setHeight(175);
            imgContainer->decorationStyle().setBorder(WBorder(BorderStyle::Solid,1,WColor(255,255,255)));
            imgContainer->setAttributeValue(Style::style,Style::background::url("test/1.jpg")+Style::background::size::cover);

            auto colorContainer = imgContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            colorContainer->setWidth(WLength("100%"));
            colorContainer->setHeight(WLength("100%"));
            colorContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));

            auto _vLayout = colorContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
            _vLayout->addStretch(1);

            auto text = _vLayout->addWidget(cpp14::make_unique<WText>("Golf"));
            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Linen)+Style::font::size::s20px+Style::font::weight::lighter);

            _vLayout->addStretch(1);

        }
        vLayout->addStretch(1);
        {
            auto _container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->setHeight(WLength("40%"));
            auto imgContainer = _container->addWidget(cpp14::make_unique<WContainerWidget>());
            imgContainer->setHeight(175);
            imgContainer->decorationStyle().setBorder(WBorder(BorderStyle::Solid,1,WColor(255,255,255)));
            imgContainer->setAttributeValue(Style::style,Style::background::url("test/2.jpg")+Style::background::size::cover);

            auto colorContainer = imgContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            colorContainer->setWidth(WLength("100%"));
            colorContainer->setHeight(WLength("100%"));
            colorContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));

            auto _vLayout = colorContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
            _vLayout->addStretch(1);

            auto text = _vLayout->addWidget(cpp14::make_unique<WText>("Basketbol"));
            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Linen)+Style::font::size::s20px+Style::font::weight::lighter);

            _vLayout->addStretch(1);
        }
        vLayout->addStretch(1);
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_4);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        {
            auto _container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->setHeight(WLength("100%"));
            auto imgContainer = _container->addWidget(cpp14::make_unique<WContainerWidget>());
            imgContainer->setHeight(400);
            imgContainer->decorationStyle().setBorder(WBorder(BorderStyle::Solid,1,WColor(255,255,255)));
            imgContainer->setAttributeValue(Style::style,Style::background::url("test/3.jpg")+Style::background::size::cover);

            auto colorContainer = imgContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            colorContainer->setWidth(WLength("100%"));
            colorContainer->setHeight(WLength("100%"));
            colorContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));

            auto _vLayout = colorContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
            _vLayout->addStretch(1);

            auto text = _vLayout->addWidget(cpp14::make_unique<WText>("Futbol"));
            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Linen)+Style::font::size::s20px+Style::font::weight::lighter);

            _vLayout->addStretch(1);
        }
        vLayout->addStretch(1);
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_4);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        {
            auto _container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->setHeight(WLength("40%"));
            auto imgContainer = _container->addWidget(cpp14::make_unique<WContainerWidget>());
            imgContainer->setHeight(175);
            imgContainer->decorationStyle().setBorder(WBorder(BorderStyle::Solid,1,WColor(255,255,255)));
            imgContainer->setAttributeValue(Style::style,Style::background::url("test/4.jpg")+Style::background::size::cover);

            auto colorContainer = imgContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            colorContainer->setWidth(WLength("100%"));
            colorContainer->setHeight(WLength("100%"));
            colorContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));

            auto _vLayout = colorContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
            _vLayout->addStretch(1);

            auto text = _vLayout->addWidget(cpp14::make_unique<WText>("Voleybol"));
            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Linen)+Style::font::size::s20px+Style::font::weight::lighter);

            _vLayout->addStretch(1);

        }
        vLayout->addStretch(1);
        {
            auto _container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->setHeight(WLength("40%"));
            auto imgContainer = _container->addWidget(cpp14::make_unique<WContainerWidget>());
            imgContainer->setHeight(175);
            imgContainer->decorationStyle().setBorder(WBorder(BorderStyle::Solid,1,WColor(255,255,255)));
            imgContainer->setAttributeValue(Style::style,Style::background::url("test/5.jpg")+Style::background::size::cover);

            auto colorContainer = imgContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            colorContainer->setWidth(WLength("100%"));
            colorContainer->setHeight(WLength("100%"));
            colorContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));

            auto _vLayout = colorContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
            _vLayout->addStretch(1);

            auto text = _vLayout->addWidget(cpp14::make_unique<WText>("Bisiklet"));
            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Linen)+Style::font::size::s20px+Style::font::weight::lighter);

            _vLayout->addStretch(1);

        }
        vLayout->addStretch(1);
    }

}
