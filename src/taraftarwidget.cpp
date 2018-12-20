#include "taraftarwidget.h"



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




    for( int i = 0 ; i < limit ; i++ )
    {
        auto item = rContainer->addWidget(cpp14::make_unique<TaraftarItem>(this->db()));
        item->addStyleClass(Bootstrap::Grid::col_full_12);
    }




//    // Foruma Katıl
//    {
//        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
//        container->addStyleClass(Bootstrap::Grid::col_full_12);
//        container->setContentAlignment(AlignmentFlag::Center);
////        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);

//        auto container_ = container->addWidget(cpp14::make_unique<WContainerWidget>());
//        container_->addStyleClass(Bootstrap::Button::Primary);
//        container_->setWidth(250);
//        container_->setHeight(35);

//        auto text = container_->addWidget(cpp14::make_unique<WText>(" Forum'a Katıl "));
//        text->setAttributeValue(Style::style,Style::font::size::s20px+Style::font::family::tahoma+Style::font::weight::lighter);
//    }





}

Signal<NoClass> &TaraftarWidget::ClickTaraftar()
{
    return _ClickTaraftar;
}

TaraftarItem::TaraftarItem(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    auto rContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);


    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(80);
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
            auto text = vLayout->addWidget(cpp14::make_unique<WText>("+14"));
            text->setAttributeValue(Style::style,Style::font::size::s18px+Style::font::weight::bold+Style::color::color(Style::color::White::Azure));
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
        container->setAttributeValue(Style::style,Style::background::color::rgb(0,114,118));
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

TaraftarPage::TaraftarPage(mongocxx::database *_db)
    :ContainerWidget ( _db )
{

    setContentAlignment(AlignmentFlag::Center);

    setMargin(50,Side::Top|Side::Bottom);

    auto rContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass( Bootstrap::Grid::row );
    rContainer->setMaximumSize(1250,WLength::Auto);



    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass( Bootstrap::Grid::col_full_12 );
        container->setContentAlignment(AlignmentFlag::Center);
        auto text = container->addWidget(cpp14::make_unique<WText>("<h3> Forum </h3>"));
    }


    {
        auto container = rContainer->addWidget(cpp14::make_unique<PersonalWidget>(this->db()));
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_3);
        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        container->ClickRequestLogin().connect(this,&TaraftarPage::initLoginPage);
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_9+Bootstrap::Grid::Medium::col_md_9+Bootstrap::Grid::Small::col_sm_9);
        for( int i = 0 ; i < 9 ; i++ )
        {
            auto item = container->addWidget(cpp14::make_unique<TaraftarItem>(this->db()));
            item->addStyleClass(Bootstrap::Grid::container_fluid);
        }
    }


}

void TaraftarPage::initLoginPage()
{

    clear();

    auto rContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);
    rContainer->setMaximumSize(500,WLength::Auto);

    {

        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        container->setPadding(50,Side::Left|Side::Right);
        container->setAttributeValue( Style::style , Style::background::color::color( Style::color::White::WhiteSmoke ) );

        container->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);
//        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        auto vLatout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

        auto title = vLatout->addWidget(cpp14::make_unique<WText>("<h3>Giriş</h3>"),0,AlignmentFlag::Center);

        auto text = vLatout->addWidget(cpp14::make_unique<WLineEdit>() , 1 , AlignmentFlag::Justify|AlignmentFlag::Middle );
        text->setPlaceholderText("Telefon Numaranızı Giriniz");

        auto text1 = vLatout->addWidget(cpp14::make_unique<WLineEdit>() , 1 , AlignmentFlag::Justify|AlignmentFlag::Middle );
        text1->setPlaceholderText("Şifrenizi Giriniz");

        auto girisBtn = vLatout->addWidget(cpp14::make_unique<WPushButton>("Giriş") , 1 , AlignmentFlag::Center|AlignmentFlag::Middle );
        girisBtn->addStyleClass(Bootstrap::Button::Primary);

        auto unuttumBtn = vLatout->addWidget(cpp14::make_unique<WPushButton>("Şifremi Unuttum") , 1 , AlignmentFlag::Center|AlignmentFlag::Middle );
        unuttumBtn->addStyleClass(Bootstrap::Button::Warning);

        auto uyeBtn = vLatout->addWidget(cpp14::make_unique<WPushButton>("Üye Ol") , 1 , AlignmentFlag::Center|AlignmentFlag::Middle );
        uyeBtn->addStyleClass(Bootstrap::Button::Success);

        uyeBtn->clicked().connect(this,&TaraftarPage::initRegisterPage);

    }

}

void TaraftarPage::initRegisterPage()
{
    clear();

    auto rContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);
    rContainer->setMaximumSize(500,WLength::Auto);

    {

        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        container->setPadding(50,Side::Left|Side::Right);
        container->setAttributeValue( Style::style , Style::background::color::color( Style::color::White::WhiteSmoke ) );

        container->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);
        //        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        auto vLatout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

        auto title = vLatout->addWidget(cpp14::make_unique<WText>("<h3>Üye Ol</h3>"),0,AlignmentFlag::Center);

        auto nickName = vLatout->addWidget(cpp14::make_unique<WLineEdit>() , 1 , AlignmentFlag::Justify|AlignmentFlag::Middle );
        nickName->setPlaceholderText("NickName Giriniz");

        auto namesurname = vLatout->addWidget(cpp14::make_unique<WLineEdit>() , 1 , AlignmentFlag::Justify|AlignmentFlag::Middle );
        namesurname->setPlaceholderText("Adınızı & Soyadınızı Giriniz");

//        auto password = vLatout->addWidget(cpp14::make_unique<WLineEdit>() , 1 , AlignmentFlag::Justify|AlignmentFlag::Middle );
//        password->setPlaceholderText("Şifrenizi Giriniz");

        auto telnumber = vLatout->addWidget(cpp14::make_unique<WLineEdit>() , 1 , AlignmentFlag::Justify|AlignmentFlag::Middle );
        telnumber->setPlaceholderText("Telefon Numarası Giriniz");

        auto yas = vLatout->addWidget(cpp14::make_unique<WLineEdit>() , 1 , AlignmentFlag::Justify|AlignmentFlag::Middle );
        yas->setPlaceholderText("Yaşınızı Giriniz");


        auto uyeBtn = vLatout->addWidget(cpp14::make_unique<WPushButton>("Kaydet") , 1 , AlignmentFlag::Center|AlignmentFlag::Middle );
        uyeBtn->addStyleClass(Bootstrap::Button::Primary);


    }
}



PersonalWidget::PersonalWidget(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    if( getLogined() )
    {
        addWidget(cpp14::make_unique<WText>("Logined"));
    }else{
        addWidget(cpp14::make_unique<WText>("Konu Açabilmek ve Yorum Yapabilmek için Lütfen Giriş Yapınız"));
        addWidget(cpp14::make_unique<WBreak>());
        auto btn = addWidget(cpp14::make_unique<WPushButton>("Giriş"));
        btn->addStyleClass(Bootstrap::Button::Primary);
        btn->clicked().connect([=](){this->_ClickRequestLogin.emit(NoClass());});
    }

}

Signal<NoClass> &PersonalWidget::ClickRequestLogin()
{
    return _ClickRequestLogin;
}
