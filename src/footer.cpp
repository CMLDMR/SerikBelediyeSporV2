#include "footer.h"
#include "inlinestyle.h"

Footer::Footer::Footer()
    :WContainerWidget()
{

    addStyleClass(Bootstrap::Grid::container_fluid);

//    addStyleClass("footerWidget");

    mMainContainerWidget = addWidget(cpp14::make_unique<WContainerWidget>());

    mMainContainerWidget->addStyleClass(Bootstrap::Grid::row);
    mMainContainerWidget->setContentAlignment(AlignmentFlag::Center);
    mMainContainerWidget->setAttributeValue(Style::style,Style::background::color::rgb(0,0,0));


    {
        auto container = mMainContainerWidget->addWidget(cpp14::make_unique<WContainerWidget>());
        auto layout = container->setLayout(cpp14::make_unique<WHBoxLayout>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);

        layout->addStretch(1);
        auto text = layout->addWidget(cpp14::make_unique<WText>("Serik Belediye Spor"));
        text->setAttributeValue(Style::style,Style::color::rgb("255,255,255"));
        layout->addStretch(1);

    }


    {
        auto container = mMainContainerWidget->addWidget(cpp14::make_unique<WContainerWidget>());
        auto layout = container->setLayout(cpp14::make_unique<WHBoxLayout>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);
        auto text = layout->addWidget(cpp14::make_unique<WText>("Bu Web Sayfası Serik Belediyesi Bilgi İşlem Müdürlüğü Tarafından Açık Kaynak Kodlu Olarak Geliştirilmektedir."));
//        text->addStyleClass("footerText");
        text->setAttributeValue(Style::style,Style::color::rgb("255,255,255"));
    }

    {
        auto container = mMainContainerWidget->addWidget(cpp14::make_unique<WContainerWidget>());
        auto layout = container->setLayout(cpp14::make_unique<WHBoxLayout>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);

        layout->addStretch(1);
        auto text = layout->addWidget(cpp14::make_unique<WText>("© Copyright 2018  "));
        text->setAttributeValue(Style::style,Style::color::rgb("255,255,255"));
        {
            Wt::WLink link = Wt::WLink("http://www.webtoolkit.eu/");
            link.setTarget(Wt::LinkTarget::NewWindow);

            std::unique_ptr<Wt::WAnchor> anchor =
                    Wt::cpp14::make_unique<Wt::WAnchor>(link,"Wt");

            layout->addWidget(std::move(anchor));
        }
        layout->addWidget(cpp14::make_unique<WText>(", "));
        {
            Wt::WLink link = Wt::WLink("http://www.qt.io/");
            link.setTarget(Wt::LinkTarget::NewWindow);

            std::unique_ptr<Wt::WAnchor> anchor =
                    Wt::cpp14::make_unique<Wt::WAnchor>(link,"Qt");

            layout->addWidget(std::move(anchor));
        }
        layout->addWidget(cpp14::make_unique<WText>(" & "));
        {
            Wt::WLink link = Wt::WLink("https://github.com/CMLDMR/SerikBelediyeSporV2/releases");
            link.setTarget(Wt::LinkTarget::NewWindow);

            std::unique_ptr<Wt::WAnchor> anchor =
                    Wt::cpp14::make_unique<Wt::WAnchor>(link,"gitHub");

            layout->addWidget(std::move(anchor));
        }
        layout->addStretch(1);

    }



}
