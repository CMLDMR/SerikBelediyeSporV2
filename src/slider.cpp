#include "slider.h"



Slider::Slider(mongocxx::database *_db)
    :ContainerWidget (_db)
{

    setMargin(0,AllSides);
//    setId("slider");

    setHeight(__Height);

    stackWidget = addWidget(cpp14::make_unique<WStackedWidget>());

    stackWidget->setHeight(__Height);

    {
        auto container = addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        container->setZIndex(10);
        container->setWidth(100);
        container->setHeight(__Height);
        container->setPositionScheme(PositionScheme::Absolute);
        container->setLeftSide(0);
        container->setTopSide(0);
        container->addStyleClass("SliderLeftRigt");

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("<"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        text->setAttributeValue(Style::style,Style::font::size::s48px+Style::color::color(Style::color::White::Snow));
        vLayout->addStretch(1);

        container->clicked().connect([&](){
            auto currentIndex = stackWidget->currentIndex();
            currentIndex--;

            if( currentIndex < 0 ) currentIndex = 3;
            stackWidget->setCurrentIndex(currentIndex);
        });

    }

    {
        auto container = addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        container->setZIndex(10);
        container->setWidth(100);
        container->setHeight(__Height);
        container->setPositionScheme(PositionScheme::Absolute);
        container->setRightSide(0);
        container->setTopSide(0);
        container->addStyleClass("SliderLeftRigt");
//        container->setAttributeValue(Style::style,container->attributeValue(Style::style)+Style::background::color::rgba(0,0,0));

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>(">"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        text->setAttributeValue(Style::style,Style::font::size::s48px+Style::color::color(Style::color::White::Snow));
        vLayout->addStretch(1);

        container->clicked().connect([&](){
            auto currentIndex = stackWidget->currentIndex();
            currentIndex++;

            if( currentIndex >= stackWidget->count() ) currentIndex = 0;
            stackWidget->setCurrentIndex(currentIndex);
        });
    }


    {
        auto container = std::make_unique<SlideItem>(this->db(),0);
        container->Click().connect([&](std::string oid){
            this->_mClick.emit(oid);
        });
        stackWidget->insertWidget(0,std::move(container));
    }

    {
        auto container = std::make_unique<SlideItem>(this->db(),1);
        container->Click().connect([&](std::string oid){
            this->_mClick.emit(oid);
        });
        stackWidget->insertWidget(1,std::move(container));
    }

    {
        auto container = std::make_unique<SlideItem>(this->db(),2);
        stackWidget->insertWidget(2,std::move(container));
    }

    {
        auto container = std::make_unique<SlideItem>(this->db(),3);
        stackWidget->insertWidget(3,std::move(container));
    }

    {
        auto container = std::make_unique<SlideItem>(this->db(),4);
        stackWidget->insertWidget(4,std::move(container));
    }


}

Signal<std::string> &Slider::mClick()
{
    return _mClick;
}

SlideItem::SlideItem(mongocxx::database *_db, const int index_)
    :ContainerWidget (_db),index(index_)
{
    setHeight(__Height);


    auto container = addWidget(cpp14::make_unique<WContainerWidget>());
    container->addStyleClass("SliderGradient");
    container->setHeight(__Height);

    container->clicked().connect([&](){
        this->_mClick.emit(mOid);
    });

    {
        auto textContainer = container->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        mTextTitle = textContainer->addWidget(cpp14::make_unique<WText>(""));
        mTextTitle->setAttributeValue(Style::style,Style::font::weight::bold+Style::font::size::s36px+Style::color::color(Style::color::Orange::Orange));
        textContainer->setPositionScheme(PositionScheme::Absolute);
        textContainer->setLeftSide(5.0);
        textContainer->setTopSide(20.0);
    }

    {
        auto textContainer = container->addWidget(cpp14::make_unique<ContainerWidget>(this->db()));
        mSmallText = textContainer->addWidget(cpp14::make_unique<WText>(""));
        mSmallText->setAttributeValue(Style::style,Style::font::weight::bold+Style::font::size::s24px+Style::color::color(Style::color::White::Azure));
        textContainer->setPositionScheme(PositionScheme::Absolute);
        textContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));
        textContainer->setLeftSide(5.0);
        textContainer->setTopSide(35.0);
    }







    auto filter = document{};


    try {
        filter.append(kvp("yayinda",true)) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << "-> filter." << "yayinda :"<< e.what() << std::endl;
    }


    auto sortDoc = document{};

    try {
        sortDoc.append(kvp("_id",-1)) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << "-> sortDoc." << "_id :"<< e.what() << std::endl;
    }


    mongocxx::options::find findOptions;

    findOptions.limit(1);
    findOptions.skip(index);

    findOptions.sort(sortDoc.view());



    try {
        auto val = this->db()->collection("Haberler").find_one(filter.view(),findOptions);
        if( val )
        {

            auto view = val.value().view();

            try {
                auto value = view["habericon"].get_oid().value.to_string();
                this->setBackGroundImg(this->downloadFile(value));

            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << "->in view habericon type is not " << "get_oid() :"<< e.what() << std::endl;
            }


            try {
                auto value = view["baslik"].get_utf8().value.to_string();
                this->setTitle(value);
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << "->in view baslik type is not " << "get_utf8() :"<< e.what() << std::endl;
            }

            try {
                auto value = view["icerikPlain"].get_utf8().value.to_string();
                this->setPlainText(value);
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << "->in view baslik type is not " << "get_utf8() :"<< e.what() << std::endl;
            }


            try {
                auto value = view["_id"].get_oid().value.to_string();
                this->setOid(value);
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << "->in view _id type is not " << "Oid :"<< e.what() << std::endl;
            }

        }else{

        }
    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
    }






//    auto imgPath = this->downloadFile("5ae6cc12ae94be18fc00097c");

//    setAttributeValue(Style::style,Style::background::url(imgPath)
//                                            +Style::background::repeat::norepeat
//                          +Style::background::position::center_center
//                          +Style::background::size::cover);








}

int SlideItem::getIndex() const
{
    return index;
}

Signal<std::string> &SlideItem::Click()
{
    return _mClick;
}

std::string SlideItem::getOid() const
{
    return mOid;
}

std::string SlideItem::getTitle() const
{
    return mTitle;
}

void SlideItem::setTitle(const std::string &title)
{
    mTitle = title;
    this->setTextTitle(mTitle);
}

std::string SlideItem::getBackGroundImg() const
{
    return mBackGroundImg;
}

void SlideItem::setBackGroundImg(const std::string &backGroundImg)
{
    mBackGroundImg = backGroundImg;
    setAttributeValue(Style::style,Style::background::url(mBackGroundImg)
                                            +Style::background::repeat::norepeat
                          +Style::background::position::center_center
                          +Style::background::size::cover);
}

std::string SlideItem::getPlainText() const
{
    return mPlainText;
}

void SlideItem::setPlainText(const std::string &plainText)
{
    mPlainText = plainText;
    mPlainText.resize(50);
    mPlainText.resize(53,'.');
    this->setSmallText(mPlainText);
}

void SlideItem::setOid(const std::string &oid)
{
    mOid = oid;
}

void SlideItem::setTextTitle(const std::string &textTitle)
{
    this->mTextTitle->setText(mTitle);
}

void SlideItem::setSmallText(const std::string &smallText)
{
    mPlainText = smallText;
    this->mSmallText->setText(mPlainText);
}
