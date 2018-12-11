#include "body.h"

#include "slider.h"
#include "haberduyurucaps.h"
#include "takimlarwidget.h"
#include "fotovideowidget.h"
#include "iletisimwidget.h"



Body::Body(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    setMargin(0,AllSides);

    addStyleClass(Bootstrap::Grid::container_fluid);

    mMainContainer = addWidget(cpp14::make_unique<WContainerWidget>());

    mMainContainer->addStyleClass(Bootstrap::Grid::row);

    this->initBody();
}

void Body::initBody()
{
    auto slider = mMainContainer->addWidget(cpp14::make_unique<Slider>(this->db()));
    slider->addStyleClass(Bootstrap::Grid::col_full_12);

    auto haberDuyuruCaps = mMainContainer->addWidget(cpp14::make_unique<HaberDuyuruCaps>(this->db()));
    haberDuyuruCaps->addStyleClass(Bootstrap::Grid::col_full_12);

    auto takimlarWidget = mMainContainer->addWidget(cpp14::make_unique<TakimlarWidget>(this->db()));
    takimlarWidget->addStyleClass(Bootstrap::Grid::col_full_12);

    auto fotoVideoWidget = mMainContainer->addWidget(cpp14::make_unique<FotoVideoWidget>(this->db()));
    fotoVideoWidget->addStyleClass(Bootstrap::Grid::col_full_12);

    auto iletisimWidget = mMainContainer->addWidget(cpp14::make_unique<IletisimWidget>(this->db()));
    iletisimWidget->addStyleClass(Bootstrap::Grid::col_full_12);
}
