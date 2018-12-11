#include "slider.h"



Slider::Slider(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    setMargin(0,AllSides);


    stackWidget = addWidget(cpp14::make_unique<WStackedWidget>());


    {
        auto container = addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        container->setZIndex(10);
        container->setWidth(100);
        container->setHeight(__Height);
        container->setPositionScheme(PositionScheme::Absolute);
        container->setLeftSide(0);
        container->setTopSide(0);

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("<"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        text->setAttributeValue(Style::style,Style::font::size::s48px+Style::color::color(Style::color::White::Snow));
        vLayout->addStretch(1);

    }

    {
        auto container = addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        container->setZIndex(10);
        container->setWidth(100);
        container->setHeight(__Height);
        container->setPositionScheme(PositionScheme::Absolute);
        container->setRightSide(0);
        container->setTopSide(0);
//        container->setAttributeValue(Style::style,container->attributeValue(Style::style)+Style::background::color::rgba(0,0,0));

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>(">"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        text->setAttributeValue(Style::style,Style::font::size::s48px+Style::color::color(Style::color::White::Snow));
        vLayout->addStretch(1);
    }


    {
        auto container = std::make_unique<SlideItem>(this->db(),3);
        stackWidget->insertWidget(0,std::move(container));
    }

    {
        auto container = std::make_unique<SlideItem>(this->db(),2);
        stackWidget->insertWidget(1,std::move(container));
    }

    {
        auto container = std::make_unique<SlideItem>(this->db(),3);
        stackWidget->insertWidget(2,std::move(container));
    }

    {
        auto container = std::make_unique<SlideItem>(this->db(),4);
        stackWidget->insertWidget(3,std::move(container));
    }

}

SlideItem::SlideItem(mongocxx::database *_db, const int index_)
    :ContainerWidget (_db),index(index_)
{
    setHeight(__Height);
    setAttributeValue(Style::style,Style::background::url("test/"+std::to_string(index)+".jpg")
                                            +Style::background::repeat::norepeat
                                            +Style::background::position::center_center
                                            +Style::background::size::cover);

    auto container = addWidget(cpp14::make_unique<WContainerWidget>());
    container->addStyleClass("SliderGradient");
    container->setHeight(__Height);


    {
        auto textContainer = container->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        auto text = textContainer->addWidget(cpp14::make_unique<WText>("Slide " + std::to_string(1)+" Title"));
        text->setAttributeValue(Style::style,Style::font::weight::bold+Style::font::size::s64px+Style::color::color(Style::color::Orange::Orange));
        textContainer->setPositionScheme(PositionScheme::Absolute);
        textContainer->setLeftSide(5.0);
        textContainer->setTopSide(20.0);
    }

    {
        auto textContainer = container->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        auto text = textContainer->addWidget(cpp14::make_unique<WText>("Slide " + std::to_string(1)+" Small Explaining..."));
        text->setAttributeValue(Style::style,Style::font::weight::bold+Style::font::size::s24px+Style::color::color(Style::color::White::Azure));
        textContainer->setPositionScheme(PositionScheme::Absolute);
        textContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));
        textContainer->setLeftSide(5.0);
        textContainer->setTopSide(35.0);
    }


}

int SlideItem::getIndex() const
{
    return index;
}
