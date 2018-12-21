#include "yenikonu.h"

YeniKonu::YeniKonu(mongocxx::database *db_)
    :ContainerWidget(db_)
{
    clear();

    auto rContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    rContainer->setMaximumSize(600,WLength::Auto);

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Center);
        auto text = container->addWidget(cpp14::make_unique<WText>("<h4>Yeni Konu Başlat</h4>"));
    }
    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Justify);
        container->setMargin(10,Side::Top|Side::Bottom);
        mTitleText = container->addWidget(cpp14::make_unique<WLineEdit>());
        mTitleText->setPlaceholderText("Konu Başlığı Giriniz");
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Justify);
        mEditor = container->addWidget(cpp14::make_unique<WTextEdit>());
        mEditor->setHeight(250);
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Center);
        auto btn = container->addWidget(cpp14::make_unique<WPushButton>("Kaydet"));
        btn->addStyleClass(Bootstrap::Button::Primary);

        btn->clicked().connect([=](){
            _ClickSave.emit(NoClass());
        });
    }
}

Signal<NoClass> &YeniKonu::ClickSave()
{
    return _ClickSave;
}

std::string YeniKonu::html() const
{
    return mEditor->text().toUTF8();
}

std::string YeniKonu::title() const
{
    return mTitleText->text().toUTF8();
}
