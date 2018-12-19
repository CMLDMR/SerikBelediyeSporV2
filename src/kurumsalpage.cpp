#include "kurumsalpage.h"

#include <utility>


KurumsalPage::KurumsalPage( mongocxx::database *_db )
    :ContainerWidget ( _db )
{

    setContentAlignment(AlignmentFlag::Center);


    auto fContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    fContainer->addStyleClass(Bootstrap::Grid::container_fluid);

    fContainer->setMaximumSize(1250,WLength::Auto);

    auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    // YONETİM KURULU TITLE
    {
        auto container_ = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->setMargin(25,Side::Top|Side::Bottom);
        container_->addStyleClass(Bootstrap::Grid::col_full_12);
        container_->setHeight(25);
        container_->setContentAlignment(AlignmentFlag::Center);
        auto text = container_->addWidget(cpp14::make_unique<WText>("Yönetim Kurulu Üyeleri"));
        text->setAttributeValue(Style::style,Style::font::size::s24px+Style::font::family::tahoma+Style::font::weight::normal);
    }

    // Kulüp Başkanı
    {
        auto container_ = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::col_full_12);
        container_->setContentAlignment(AlignmentFlag::Center);
//        container_->setAttributeValue(Style::style,Style::background::color::color(Style::color::Pink::HotPink));
//        container_->addStyleClass(Bootstrap::ImageShape::img_thumbnail);

        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setWidth(120);
        container->setHeight(160);
        container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Purple::SlateBlue));
        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);

        auto _container = container->addWidget(cpp14::make_unique<WContainerWidget>());
        _container->setWidth(WLength("100%"));
        _container->setHeight(WLength("100%"));
        _container->setAttributeValue( Style::style , Style::background::url("img/person.png")+Style::background::size::contain+Style::background::repeat::norepeat+Style::background::position::center_center);

        {
            container_->addWidget(cpp14::make_unique<WBreak>());
            auto text = container_->addWidget(cpp14::make_unique<WText>("Ali AKSU"));
        }
        {
            container_->addWidget(cpp14::make_unique<WBreak>());
            auto text = container_->addWidget(cpp14::make_unique<WText>("Kulüp Başkanı"));
        }
    }

    // Kulüp AS Başkanı
    {
        auto container_ = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::col_full_12);
        container_->setContentAlignment(AlignmentFlag::Center);
        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setWidth(115);
        container->setHeight(150);
        container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Purple::Plum));
        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);

        auto _container = container->addWidget(cpp14::make_unique<WContainerWidget>());
        _container->setWidth(WLength("100%"));
        _container->setHeight(WLength("100%"));
        _container->setAttributeValue( Style::style , Style::background::url("img/person.png")+Style::background::size::contain+Style::background::repeat::norepeat+Style::background::position::center_center);

        {
            container_->addWidget(cpp14::make_unique<WBreak>());
            auto text = container_->addWidget(cpp14::make_unique<WText>("Nebi KIR"));
        }
        {
            container_->addWidget(cpp14::make_unique<WBreak>());
            auto text = container_->addWidget(cpp14::make_unique<WText>("As Başkanı"));
        }
    }

    // Kulüp Başkan Yardımcıları
    {
        std::vector<std::pair<std::string,std::string>> bskYrd;

        bskYrd.push_back(std::make_pair("Recep Şamil YAŞACAN","Başkan Yardımcısı"));
        bskYrd.push_back(std::make_pair("Mustafa KARA","Başkan Yardımcısı"));
        bskYrd.push_back(std::make_pair("Nida GÖKOĞLU","Başkan Yardımcısı"));
        bskYrd.push_back(std::make_pair("Levent KONUR","Başkan Yardımcısı"));

        for( auto item : bskYrd )
        {

            auto container_ = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            container_->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
            container_->setContentAlignment(AlignmentFlag::Center);
            auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
            container->setWidth(100);
            container->setHeight(130);
            container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Pink::LightPink));
            container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
            {
                container_->addWidget(cpp14::make_unique<WBreak>());
                auto text = container_->addWidget(cpp14::make_unique<WText>(item.first));
            }
            {
                container_->addWidget(cpp14::make_unique<WBreak>());
                auto text = container_->addWidget(cpp14::make_unique<WText>(item.second));
            }

        }
    }


    // Kulüp Genel Sekreteri
    {
        auto container_ = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::col_full_12);
        container_->setContentAlignment(AlignmentFlag::Center);
        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setWidth(100);
        container->setHeight(130);
        container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Pink::MediumVioletRed));
        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        {
            container_->addWidget(cpp14::make_unique<WBreak>());
            auto text = container_->addWidget(cpp14::make_unique<WText>("Bünyamin OKUDAN"));
        }
        {
            container_->addWidget(cpp14::make_unique<WBreak>());
            auto text = container_->addWidget(cpp14::make_unique<WText>("Genel Sekreter"));
        }
    }


    // Kulüp Sorumluları
    {
        std::vector<std::pair<std::string,std::string>> bskYrd;

        bskYrd.push_back(std::make_pair("İsmail KÖKALIŞLAR","Futbol Şube Sorumlusu"));
        bskYrd.push_back(std::make_pair("Ali KUMBUL","Alt Yapı Sorumlusu"));
        bskYrd.push_back(std::make_pair("Yusuf KARASU","Alt Yapı Sorumlusu"));
        bskYrd.push_back(std::make_pair("Ramazan KAÇAR","Hukuk Sorumlusu"));
        bskYrd.push_back(std::make_pair("Yusuf AKÇEHRE","Sayman"));
        bskYrd.push_back(std::make_pair("Namık Kemal KILINÇ","Basın Sözcüsü"));
        bskYrd.push_back(std::make_pair("Yunus ÖZPARLAR","Sosyal Medya Sorumlusu"));
        bskYrd.push_back(std::make_pair("Cengiz DOĞAN","Tarafdarlardan Sorumlu"));

        for( auto item : bskYrd ){
            auto container_ = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            container_->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_3+Bootstrap::Grid::ExtraSmall::col_xs_4);
            container_->setContentAlignment(AlignmentFlag::Center);
            auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
            container->setWidth(90);
            container->setHeight(120);
            container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Pink::PaleVioletRed));
            container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
            {
                container_->addWidget(cpp14::make_unique<WBreak>());
                auto text = container_->addWidget(cpp14::make_unique<WText>(item.first));
            }
            {
                container_->addWidget(cpp14::make_unique<WBreak>());
                auto text = container_->addWidget(cpp14::make_unique<WText>(item.second));
            }
        }
    }

    // Kulüp Genel Sekreteri
    {
        auto container_ = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::col_full_12);
        container_->setHeight(25);
    }

    // Kulüp Başkan Yardımcıları
    {
        std::vector<std::pair<std::string,std::string>> bskYrd;

        bskYrd.push_back(std::make_pair("Halil KİRLİ","Kulüp Müdürü"));
        bskYrd.push_back(std::make_pair("Erhan KAŞ","Kulüp Müdür Yardımcısı"));
        bskYrd.push_back(std::make_pair("Musa UYGUN","Kulüp Muhasebesi"));
        bskYrd.push_back(std::make_pair("Hüseyin BANKOĞLU","Kulüp Doktoru"));
        bskYrd.push_back(std::make_pair("Hasan TEKER","Güreş Koordinatörü"));
        bskYrd.push_back(std::make_pair("Süleyman ÖGEN","Alt Yapı Genel Koordinatörü"));

        for( auto item : bskYrd ){
            auto container_ = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            container_->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_3+Bootstrap::Grid::ExtraSmall::col_xs_4);
            container_->setContentAlignment(AlignmentFlag::Center);
            auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
            container->setWidth(80);
            container->setHeight(110);
            container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Purple::Orchid));
            container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
            {
                container_->addWidget(cpp14::make_unique<WBreak>());
                auto text = container_->addWidget(cpp14::make_unique<WText>(item.first));
            }
            {
                container_->addWidget(cpp14::make_unique<WBreak>());
                auto text = container_->addWidget(cpp14::make_unique<WText>(item.second));
            }
        }
    }

    rContainer->setMargin(25,Side::Bottom);
}
