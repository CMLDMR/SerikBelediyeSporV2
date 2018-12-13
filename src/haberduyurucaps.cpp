#include "haberduyurucaps.h"

HaberDuyuruCaps::HaberDuyuruCaps(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    setHeight(200);




    {
        auto cContainer = addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        cContainer->setWidth(WLength("70%"));
        cContainer->setHeight(250);
        cContainer->setPositionScheme(PositionScheme::Absolute);
        cContainer->setLeftSide(15.0);
        cContainer->setTopSide(-150);

            {
                auto container = cContainer->addWidget(cpp14::make_unique<HaberDuyuruCapsItem>(this->db(),true));
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_5
                                         +Bootstrap::Grid::Medium::col_md_5
                                         +Bootstrap::Grid::Small::col_sm_5
                                         +Bootstrap::Grid::ExtraSmall::col_xs_12);
                container->setHeight(WLength("100%"));
            }

            {
                auto container = cContainer->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_2
                                         +Bootstrap::Grid::Medium::col_md_2
                                         +Bootstrap::Grid::Small::col_sm_2
                                         +Bootstrap::Grid::ExtraSmall::col_xs_12);
                container->setHeight(WLength("0%"));
            }

            {
                auto container = cContainer->addWidget(cpp14::make_unique<HaberDuyuruCapsItem>(this->db()));
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_5
                                         +Bootstrap::Grid::Medium::col_md_5
                                         +Bootstrap::Grid::Small::col_sm_5
                                         +Bootstrap::Grid::ExtraSmall::col_xs_12);
                container->setHeight(WLength("100%"));
            }

    }



}

HaberDuyuruCapsItem::HaberDuyuruCapsItem(mongocxx::database *_db, bool m_Haber)
    :ContainerWidget (_db)
{
    if( m_Haber )
    {
        setBackGroundImage("test/3.jpg");
    }else{
        setBackGroundImage("test/2.jpg");
    }


    auto container = addWidget(cpp14::make_unique<WContainerWidget>());
    container->setWidth(WLength("100%"));
    container->setHeight(WLength("100%"));
    container->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));

    auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

    vLayout->addStretch(1);
    std::string mCurrentTitle = m_Haber ? "Haber" : "Duyurular";
    auto haberTitle = vLayout->addWidget(cpp14::make_unique<WText>(mCurrentTitle),0,AlignmentFlag::Center|AlignmentFlag::Middle);
    haberTitle->setAttributeValue(Style::style,Style::font::size::s20px+Style::color::color(Style::color::White::White));

    vLayout->addStretch(1);

    mCurrentTitle = m_Haber ? "Serik Belediye Spor Profesyonel Ligte" : "Yeni Müsabaka";
    auto ContentTitle = vLayout->addWidget(cpp14::make_unique<WText>(mCurrentTitle),0,AlignmentFlag::Center|AlignmentFlag::Middle);
    ContentTitle->setAttributeValue(Style::style,Style::font::size::s24px
                                        +Style::font::weight::bold
                                        +Style::color::color(Style::color::Orange::DarkOrange));
    vLayout->addStretch(1);

    {
        auto _Container = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        _Container->decorationStyle().setBorder(WBorder(BorderStyle::Solid,2,WColor(255,255,255)));
        _Container->setPadding(10,AllSides);
        _Container->setPadding(25,Side::Right|Side::Left);
        mCurrentTitle = "Detay";
        auto DetayTitle = _Container->addWidget(cpp14::make_unique<WText>(mCurrentTitle));
    DetayTitle->setAttributeValue(Style::style,Style::font::size::s18px
                                          +Style::font::weight::lighter
                                          +Style::color::color(Style::color::White::AliceBlue));
    }
    vLayout->addStretch(1);
}



