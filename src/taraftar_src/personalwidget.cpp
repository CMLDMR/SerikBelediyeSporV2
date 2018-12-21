#include "personalwidget.h"
#include "src/body.h"
#include "src/taraftar_src/yenikonu.h"
#include "src/taraftar_src/taraftaritem.h"


PersonalWidget::PersonalWidget(mongocxx::database *_db, bsoncxx::document::value personelValue)
    :ContainerWidget (_db,personelValue)
{

    if( getLogined() )
    {
        this->initPersonel();
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

Signal<NoClass> &PersonalWidget::ClickNewKonu()
{
    return _ClickNewKonu;
}

void PersonalWidget::initPersonel()
{
    auto rContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->addWidget(cpp14::make_unique<WText>(this->nickname()));
        container->setMargin(15,Side::Top|Side::Bottom);
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->addWidget(cpp14::make_unique<WText>(this->getIsim()));
        container->setMargin(15,Side::Top|Side::Bottom);
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->addWidget(cpp14::make_unique<WText>(this->getTel()));
        container->setMargin(15,Side::Top|Side::Bottom);
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        auto btn = container->addWidget(cpp14::make_unique<WPushButton>("Yeni Konu"));
        btn->addStyleClass(Bootstrap::Button::Primary);
        btn->clicked().connect([=](){
            _ClickNewKonu.emit(NoClass());
        });
        container->setMargin(15,Side::Top|Side::Bottom);
    }
}
