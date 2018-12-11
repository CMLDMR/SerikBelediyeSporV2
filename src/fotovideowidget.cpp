#include "fotovideowidget.h"

FotoVideoWidget::FotoVideoWidget(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    setMargin(100,Side::Top|Side::Bottom);
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
            _container->addStyleClass(Bootstrap::Grid::Large::col_lg_6);
            _container->setContentAlignment(AlignmentFlag::Right);
            auto text = _container->addWidget(cpp14::make_unique<WText>("Fotoğraf"));
            text->setAttributeValue(Style::style,Style::font::size::s36px+Style::font::weight::bold+Style::color::color(Style::color::Orange::Coral));
        }

        {
            auto _container = _rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->addStyleClass(Bootstrap::Grid::Large::col_lg_6);
            _container->setContentAlignment(AlignmentFlag::Left);
            auto text = _container->addWidget(cpp14::make_unique<WText>("Video"));
            text->setAttributeValue(Style::style,Style::font::size::s36px+Style::font::weight::bold+Style::color::color(Style::color::Green::DarkGreen));
        }
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_12);

        auto _mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        _mContainer->addStyleClass(Bootstrap::Grid::container_fluid);
        _mContainer->setAttributeValue(Style::style,Style::background::url("test/1.jpg")+Style::background::size::cover);
        _mContainer->setHeight(250);

        auto vLayout = _mContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

        vLayout->addStretch(1);

        auto _rContainer = _mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        _rContainer->addStyleClass(Bootstrap::Grid::row);
        {
            auto __container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Justify);
            __container->setAttributeValue(Style::style,Style::background::color::rgba(255,255,255,0.90));
            __container->setContentAlignment(AlignmentFlag::Center);
            auto text = __container->addWidget(cpp14::make_unique<WText>("1992"));
            text->setMargin(WLength::Auto,Side::Left|Side::Right);
            text->setAttributeValue(Style::style,Style::font::size::s16px+Style::font::weight::bold+Style::color::color(Style::color::Orange::Coral));
        }
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_12);

        auto _mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        _mContainer->addStyleClass(Bootstrap::Grid::container_fluid);
        _mContainer->setAttributeValue(Style::style,Style::background::url("test/3.jpg")+Style::background::size::cover);
        _mContainer->setHeight(250);

        auto vLayout = _mContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

        vLayout->addStretch(1);

        auto _rContainer = _mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        _rContainer->addStyleClass(Bootstrap::Grid::row);
        {
            auto __container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Justify);
            __container->setAttributeValue(Style::style,Style::background::color::rgba(255,255,255,0.90));
            __container->setContentAlignment(AlignmentFlag::Center);
            auto text = __container->addWidget(cpp14::make_unique<WText>("1992"));
            text->setMargin(WLength::Auto,Side::Left|Side::Right);
            text->setAttributeValue(Style::style,Style::font::size::s16px+Style::font::weight::bold+Style::color::color(Style::color::Orange::Coral));
        }
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_12);

        auto _mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        _mContainer->addStyleClass(Bootstrap::Grid::container_fluid);
        _mContainer->setAttributeValue(Style::style,Style::background::url("test/2.jpg")+Style::background::size::cover);
        _mContainer->setHeight(250);

        auto vLayout = _mContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

        vLayout->addStretch(1);

        auto _rContainer = _mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        _rContainer->addStyleClass(Bootstrap::Grid::row);
        {
            auto __container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Justify);
            __container->setAttributeValue(Style::style,Style::background::color::rgba(255,255,255,0.90));
            __container->setContentAlignment(AlignmentFlag::Center);
            auto text = __container->addWidget(cpp14::make_unique<WText>("1992"));
            text->setMargin(WLength::Auto,Side::Left|Side::Right);
            text->setAttributeValue(Style::style,Style::font::size::s16px+Style::font::weight::bold+Style::color::color(Style::color::Orange::Coral));
        }
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_12);

        auto _mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        _mContainer->addStyleClass(Bootstrap::Grid::container_fluid);
        _mContainer->setAttributeValue(Style::style,Style::background::url("test/4.jpg")+Style::background::size::cover);
        _mContainer->setHeight(250);

        auto vLayout = _mContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

        vLayout->addStretch(1);

        auto _rContainer = _mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        _rContainer->addStyleClass(Bootstrap::Grid::row);
        {
            auto __container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Justify);
            __container->setAttributeValue(Style::style,Style::background::color::rgba(255,255,255,0.90));
            __container->setContentAlignment(AlignmentFlag::Center);
            auto text = __container->addWidget(cpp14::make_unique<WText>("1992"));
            text->setMargin(WLength::Auto,Side::Left|Side::Right);
            text->setAttributeValue(Style::style,Style::font::size::s16px+Style::font::weight::bold+Style::color::color(Style::color::Orange::Coral));
        }
    }
}
