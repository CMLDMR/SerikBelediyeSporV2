#include "header.h"

#include <Wt/WNavigationBar.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPopupMenuItem.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WToolBar.h>
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>


Header::Header(mongocxx::database *db)
    :ContainerWidget (db)
{

    addStyleClass(Bootstrap::Grid::container_fluid);
    setContentAlignment(AlignmentFlag::Center);

//    setBorder(StandardColor::Gray);

    setHeight(175);


    mContentContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    mContentContainer->addStyleClass(Bootstrap::Grid::row);
    mContentContainer->setMaximumSize(1440,WLength::Auto);


//    mContentContainer = row->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
////    mContentContainer->setBorder(StandardColor::Red);
//    mContentContainer->addStyleClass(Bootstrap::Grid::col_full_12);

    // Serik Belediye Spor Logo
    {
        this->PlaceLogo();
    }

    // Serik Belediye Spor
    {
        this->PlaceSerik();
    }

    // Serik Belediyesi ToolBar Menu
    {
        this->PlaceToolBar();
    }



}

Signal<NoClass> &Header::ClickAnaSayfa()
{

    return _ClickAnasayfa;

}

Signal<NoClass> &Header::ClickKurumsal()
{

    return _ClickKurumsal;

}

Signal<NoClass> &Header::ClickHaberler()
{

    return _ClickHaberler;

}

Signal<NoClass> &Header::ClickDuyurular()
{

    return _ClickDuyurular;

}

Signal<NoClass> &Header::ClickGaleri()
{
    return _ClickGaleri;
}

Signal<NoClass> &Header::ClickHakkinda()
{
    return _ClickHakkinda;
}

void Header::PlaceLogo()
{

    auto logoContainer = mContentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        logoContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_1
                                     +Bootstrap::Grid::Medium::col_md_1
                                 +Bootstrap::Grid::Small::col_sm_2
                                 +Bootstrap::Grid::ExtraSmall::col_xs_2);
        logoContainer->setHeight(100);
        logoContainer->setAttributeValue(Style::style,Style::background::url("img/logo.png")
                                             +Style::background::repeat::norepeat
                                             +Style::background::position::center_center
                                             +Style::background::size::contain);

        logoContainer->clicked().connect([=](){
            _ClickAnasayfa.emit(NoClass());
        });
        logoContainer->decorationStyle().setCursor(Cursor::PointingHand);


}

void Header::PlaceSerik()
{

    auto menubarContainer = mContentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    menubarContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_11
                                    +Bootstrap::Grid::Medium::col_md_11
                                    +Bootstrap::Grid::Small::col_sm_10
                                    +Bootstrap::Grid::ExtraSmall::col_xs_10);
    menubarContainer->setHeight(100);



    auto menucontainer = menubarContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    menucontainer->addStyleClass(Bootstrap::Grid::container_fluid);

    auto rRow = menucontainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rRow->addStyleClass(Bootstrap::Grid::row);

    {
        auto container = rRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_6
                                 +Bootstrap::Grid::Medium::col_md_6
                                 +Bootstrap::Grid::Small::col_sm_12
                                 +Bootstrap::Grid::ExtraSmall::col_xs_12);
        container->setContentAlignment(AlignmentFlag::Right);


        container->setAttributeValue(Style::style,Style::background::url("img/text.png")
                                         +Style::background::repeat::norepeat
                                         +Style::background::position::left_center
                                         +Style::background::size::contain);

        container->setHeight(100);
        container->decorationStyle().setCursor(Cursor::PointingHand);
//        container->addStyleClass("logoContainer");


    }

    {
        auto container = rRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3
                                 +Bootstrap::Grid::Medium::col_md_3
                                 +Bootstrap::Grid::Small::col_sm_6
                                 +Bootstrap::Grid::ExtraSmall::col_xs_6);

        container->addStyleClass(Bootstrap::Grid::Hidden::hidden_sm+Bootstrap::Grid::Hidden::hidden_xs);



        auto _vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

        _vLayout->addStretch(1);

        {
            auto text = _vLayout->addWidget(cpp14::make_unique<WText>("e-Mail"));
            text->setAttributeValue(Style::style,Style::font::size::s14px
                                        +Style::font::weight::lighter
                                        +Style::color::rgb("25,92,48"));
        }
        {
            auto text = _vLayout->addWidget(cpp14::make_unique<WText>("info@serikbelediyespor.com"));
            text->setAttributeValue(Style::style,Style::font::size::s14px
                                        +Style::font::weight::bold
                                        +Style::color::rgb("25,92,48"));
        }

        _vLayout->addStretch(1);

        container->setHeight(100);
    }

    {
        auto container = rRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3
                                 +Bootstrap::Grid::Medium::col_md_3
                                 +Bootstrap::Grid::Small::col_sm_6
                                 +Bootstrap::Grid::ExtraSmall::col_xs_6);
        container->addStyleClass(Bootstrap::Grid::Hidden::hidden_sm+Bootstrap::Grid::Hidden::hidden_xs);

        auto _vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

        _vLayout->addStretch(1);

        {
            auto text = _vLayout->addWidget(cpp14::make_unique<WText>("İletişim"));
            text->setAttributeValue(Style::style,Style::font::size::s14px
                                        +Style::font::weight::lighter
                                        +Style::color::rgb("25,92,48"));
        }
        {
            auto text = _vLayout->addWidget(cpp14::make_unique<WText>("444 9 722"));
            text->setAttributeValue(Style::style,Style::font::size::s14px
                                        +Style::font::weight::bold
                                        +Style::color::rgb("25,92,48"));
        }

        _vLayout->addStretch(1);

        container->setHeight(100);
    }


    menucontainer->clicked().connect([=](){
        _ClickAnasayfa.emit(NoClass());
    });


}

void Header::PlaceToolBar()
{

    auto menubarContainer = mContentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    menubarContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    menubarContainer->setHeight(60);
    menubarContainer->setAttributeValue(Style::Affix::data_spy,Style::Affix::affix);

    auto row = menubarContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    row->addStyleClass(Bootstrap::Grid::row+Bootstrap::ImageShape::img_thumbnail);
    row->setWidth(WLength("100%"));


    const int menuBarHeight = 50;
    // 1. Ana Sayfa Butonu
    {
        auto menuContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        menuContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_2
                                     +Bootstrap::Grid::Medium::col_md_2
                                     +Bootstrap::Grid::Small::col_sm_2
                                     +Bootstrap::Grid::ExtraSmall::col_xs_2);
//        menuContainer->setAttributeValue(Style::style,Style::background::color::rgb(0,30,10));
        menuContainer->setHeight(menuBarHeight);
        menuContainer->addStyleClass("menuBar");


        auto vLayout = menuContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("<span style=\"color:white;\">Kurumsal</span>",TextFormat::XHTML),0,AlignmentFlag::Justify);
        text->setAttributeValue(Style::style,Style::font::family::tahoma);
        vLayout->addStretch(1);
        menuContainer->clicked().connect([=](){
            this->_ClickKurumsal.emit(NoClass());
        });
    }

    // 2. Haberler
    {
        auto menuContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        menuContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_2
                                     +Bootstrap::Grid::Medium::col_md_2
                                     +Bootstrap::Grid::Small::col_sm_2
                                     +Bootstrap::Grid::ExtraSmall::col_xs_2);
//        menuContainer->setAttributeValue(Style::style,Style::background::color::rgb(0,30,10));
        menuContainer->setHeight(menuBarHeight);
        menuContainer->addStyleClass("menuBar");

        auto vLayout = menuContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("<span style=\"color:white;\">Haberler</span>",TextFormat::XHTML),0,AlignmentFlag::Center);
        text->setAttributeValue(Style::style,Style::font::family::tahoma);
        vLayout->addStretch(1);

        menuContainer->clicked().connect([=](){
            this->_ClickHaberler.emit(NoClass());
        });
    }

    // 3. Duyurular
    {
        auto menuContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        menuContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_2
                                     +Bootstrap::Grid::Medium::col_md_2
                                     +Bootstrap::Grid::Small::col_sm_2
                                     +Bootstrap::Grid::ExtraSmall::col_xs_2);
//        menuContainer->setAttributeValue(Style::style,Style::background::color::rgb(0,30,10));
        menuContainer->setHeight(menuBarHeight);
        menuContainer->addStyleClass("menuBar");

        auto vLayout = menuContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("<span style=\"color:white;\">Duyurular</span>",TextFormat::XHTML),0,AlignmentFlag::Justify);
        text->setAttributeValue(Style::style,Style::font::family::tahoma);
        vLayout->addStretch(1);
        menuContainer->clicked().connect([=](){
            this->_ClickDuyurular.emit(NoClass());
        });
    }

    // 4. Galeri
    {
        auto menuContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        menuContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_2
                                     +Bootstrap::Grid::Medium::col_md_2
                                     +Bootstrap::Grid::Small::col_sm_2
                                     +Bootstrap::Grid::ExtraSmall::col_xs_2);
//        menuContainer->setAttributeValue(Style::style,Style::background::color::rgb(0,30,10));
        menuContainer->setHeight(menuBarHeight);
        menuContainer->addStyleClass("menuBar");

        auto vLayout = menuContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("<span style=\"color:white;\">Galeri</span>",TextFormat::XHTML),0,AlignmentFlag::Justify);
        text->setAttributeValue(Style::style,Style::font::family::tahoma);
        vLayout->addStretch(1);
        menuContainer->clicked().connect([=](){
            this->_ClickGaleri.emit(NoClass());
        });
    }

    // 5. Taraftar
    {
        auto menuContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        menuContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_2
                                     +Bootstrap::Grid::Medium::col_md_2
                                     +Bootstrap::Grid::Small::col_sm_2
                                     +Bootstrap::Grid::ExtraSmall::col_xs_2);
//        menuContainer->setAttributeValue(Style::style,Style::background::color::rgb(0,30,10));
        menuContainer->setHeight(menuBarHeight);
        menuContainer->addStyleClass("menuBar");

        auto vLayout = menuContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("<span style=\"color:white;\">Taraftar</span>",TextFormat::XHTML),0,AlignmentFlag::Justify);
        text->setAttributeValue(Style::style,Style::font::family::tahoma);
        vLayout->addStretch(1);
    }

    // 6. Hakkımızda
    {
        auto menuContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        menuContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_2
                                     +Bootstrap::Grid::Medium::col_md_2
                                     +Bootstrap::Grid::Small::col_sm_2
                                     +Bootstrap::Grid::ExtraSmall::col_xs_2);
//        menuContainer->setAttributeValue(Style::style,Style::background::color::rgb(0,30,10));
        menuContainer->setHeight(menuBarHeight);
        menuContainer->addStyleClass("menuBar");

        auto vLayout = menuContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("<span style=\"color:white;\">Hakkımızda</span>",TextFormat::XHTML),0,AlignmentFlag::Justify);
        text->setAttributeValue(Style::style,Style::font::family::tahoma);
        vLayout->addStretch(1);
        menuContainer->clicked().connect([=](){
            this->_ClickHakkinda.emit(NoClass());
        });
    }

}
