#include "taraftarpage.h"

#include "src/body.h"
#include "src/taraftar_src/yenikonu.h"
#include "src/taraftar_src/taraftaritem.h"
#include "src/taraftarwidget.h"
#include "src/taraftar_src/personalwidget.h"
#include "cevapitem.h"

TaraftarPage::TaraftarPage(Body *_mBody)
    :ContainerWidget ( _mBody->db() ) , mBody( _mBody )
{

    setContentAlignment(AlignmentFlag::Center);

    setMargin(50,Side::Top|Side::Bottom);

    this->initStartupPage();

}

void TaraftarPage::initStartupPage()
{

    clear();


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
        mPersonWidget = rContainer->addWidget(cpp14::make_unique<PersonalWidget>(this->db(),this->getPersonelValue()));
        mPersonWidget->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_3);
        mPersonWidget->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        mPersonWidget->ClickRequestLogin().connect(this,&TaraftarPage::initLoginPage);
        mPersonWidget->ClickNewKonu().connect(this,&TaraftarPage::initNewKonuPage);
    }

    {
        mContainerWidget = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        mContainerWidget->addStyleClass(Bootstrap::Grid::Large::col_lg_9+Bootstrap::Grid::Medium::col_md_9+Bootstrap::Grid::Small::col_sm_9);


        auto filter = document{};

        // TODO: Kullanımda Açılacak. Deneme Amaaçlı Kapalı
        //        try {
        //            filter.append(kvp("onay",true)) ;
        //        } catch (bsoncxx::exception &e) {
        //            std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> filter." << "onay :"<< e.what() << std::endl;
        //        }


        mongocxx::options::find findOptions;

        auto sortDoc = document{};


        try {
            sortDoc.append(kvp("updated",-1)) ;
        } catch (bsoncxx::exception &e) {
            std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> sortDoc." << "updated :"<< e.what() << std::endl;
        }


        //        findOptions.limit(12)
        findOptions.sort(sortDoc.view());


        try {

            auto cursor = this->db()->collection("forum").find(filter.view(),findOptions);

            for( auto doc : cursor )
            {
                auto item = mContainerWidget->addWidget(cpp14::make_unique<TaraftarItem>(this->db(),doc));
                item->addStyleClass(Bootstrap::Grid::container_fluid);
                item->ClickTaraftarItem().connect(this,&TaraftarPage::initItemPage);
            }
        } catch (mongocxx::exception &e) {
            std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
        }
    }
}

void TaraftarPage::initItemPage(std::string mOid)
{


    {
        auto filter = document{};
        try {
            filter.append(kvp("_id",bsoncxx::oid{mOid})) ;
        } catch (bsoncxx::exception &e) {
            std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> filter." << "_id :"<< e.what() << std::endl;
        }

        bsoncxx::document::value mValue(document{});


        try {

            auto val = this->db()->collection("forum").find_one(filter.view());

            if( val )
            {
                if( val->view().empty() )
                {
                    this->ShowMessage("Uyarı","İçerik Görüntülenemiyor");
                }else{
                    mContainerWidget->clear();


                    {
                        auto container = mContainerWidget->addWidget(cpp14::make_unique<WContainerWidget>());
                        container->setWidth(WLength("100%"));
                        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
                        container->setContentAlignment(AlignmentFlag::Center);





                        {
                            auto _container = container->addWidget(cpp14::make_unique<WContainerWidget>());
                            _container->addStyleClass(Bootstrap::Grid::container_fluid);

                            auto _rContainer = _container->addWidget(cpp14::make_unique<WContainerWidget>());
                            _rContainer->addStyleClass(Bootstrap::Grid::row);


                            {
                                auto itemContainer = _rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                                itemContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_1+Bootstrap::Grid::Medium::col_md_1+Bootstrap::Grid::Small::col_sm_2+Bootstrap::Grid::ExtraSmall::col_xs_12);
                                itemContainer->setAttributeValue(Style::style,Style::background::color::rgb(131,98,77)+Style::Border::borderRardius("3","3","3","3"));
                                int artiOy = 0;
                                int eksiOy = 0;

                                try {
                                    auto value = val->view()["+oy"].get_int32().value;
                                    artiOy = value;
                                    container->addWidget(cpp14::make_unique<WBreak>());
                                } catch (bsoncxx::exception &e) {
                                std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in val->view() saat type is not utf8() :" + std::string(e.what());
                                std::cout << err << std::endl;
                                }

                                try {
                                    auto value = val->view()["-oy"].get_int32().value;
                                    eksiOy = value;
                                    container->addWidget(cpp14::make_unique<WBreak>());
                                } catch (bsoncxx::exception &e) {
                                std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in val->view() saat type is not utf8() :" + std::string(e.what());
                                std::cout << err << std::endl;
                                }

                                auto vLayout = itemContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

                                vLayout->addWidget(cpp14::make_unique<WText>("▲"),0,AlignmentFlag::Center);
                                auto rateText = vLayout->addWidget(cpp14::make_unique<WText>(std::to_string(artiOy-eksiOy)),0,AlignmentFlag::Center);
                                if( artiOy > eksiOy )
                                {
                                    rateText->setAttributeValue(Style::style,Style::color::color(Style::color::Green::Green));
                                }else if(artiOy == eksiOy ){
                                    rateText->setAttributeValue(Style::style,Style::color::color(Style::color::White::Snow));
                                }else{
                                    rateText->setAttributeValue(Style::style,Style::color::color(Style::color::Red::Red));
                                }
                                vLayout->addWidget(cpp14::make_unique<WText>("▼"),0,AlignmentFlag::Center);
                            }
                            {
                                auto itemContainer = _rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                                itemContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_11+Bootstrap::Grid::Medium::col_md_11+Bootstrap::Grid::Small::col_sm_10+Bootstrap::Grid::ExtraSmall::col_xs_12);
                                auto vLayout = itemContainer->setLayout(cpp14::make_unique<WVBoxLayout>());


                                try {
                                    auto value = val->view()["nick"].get_utf8().value.to_string();
                                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(value));
                                } catch (bsoncxx::exception &e) {
                                std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in val->view() nick type is not get_utf8() :" + std::string(e.what());
                                std::cout << err << std::endl;
                                }

                                try {
                                    auto value = val->view()["baslik"].get_utf8().value.to_string();
                                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(value));
                                } catch (bsoncxx::exception &e) {
                                std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in val->view() baslik type is not get_utf8() :" + std::string(e.what());
                                std::cout << err << std::endl;
                                }

                                try {
                                    auto value = val->view()["julianDate"].get_int64().value;
                                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(QDate::fromJulianDay(value).toString("dd/MM/yyyy dddd").toStdString()));
                                } catch (bsoncxx::exception &e) {
                                std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in val->view() julianDate type is not get_int64() :" + std::string(e.what());
                                std::cout << err << std::endl;
                                }
                            }
                        }

                        {
                            try {
                                auto value = val->view()["html"].get_utf8().value.to_string();
                                auto text = container->addWidget(cpp14::make_unique<WText>(value,TextFormat::XHTML));

                                container->addWidget(cpp14::make_unique<WBreak>());
                            } catch (bsoncxx::exception &e) {
                            std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in val->view() html type is not utf8() :" + std::string(e.what());
                            std::cout << err << std::endl;
                            }
                        }
                    }

                    {

                        bsoncxx::array::view commentList;
                        bool existComments = false;

                        try {
                            auto value = val.value().view()["comments"].get_array().value;
                            commentList = value;
                            existComments = true;
                        } catch (bsoncxx::exception &e) {
                        std::string err =  std::string("File: ") + __FILE__ + std::string(" Line ") + std::to_string(__LINE__) + " Func: " + std::string(__FUNCTION__) + "->in val.value().view() comments type is not get_array() :" + std::string(e.what());
                        std::cout << err << std::endl;
                        }

                        if( existComments )
                        {
                            for( auto item : commentList )
                            {

                                auto container = mContainerWidget->addWidget(cpp14::make_unique<WContainerWidget>());
                                container->setWidth(WLength("100%"));
                                container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
                                container->setContentAlignment(AlignmentFlag::Center);
                                container->setMargin(15,Side::Top|Side::Bottom);
                                container->addWidget(cpp14::make_unique<CevapItem>(this->db(),item.get_document().view()));

                            }
                        }





                    }

                    {


                        auto container = mContainerWidget->addWidget(cpp14::make_unique<WContainerWidget>());
                        container->setWidth(WLength("100%"));
//                        container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
                        container->setContentAlignment(AlignmentFlag::Center);
                        container->setMargin(15,Side::Top|Side::Bottom);
                        container->setPadding(10,AllSides);

                        if( this->getLogined() )
                        {
                            auto text = container->addWidget(cpp14::make_unique<WText>("Cevap Yaz"));
                            container->addWidget(cpp14::make_unique<WBreak>());
                            auto textEdit = container->addWidget(cpp14::make_unique<WTextEdit>());
                            textEdit->setHeight(250);
                            container->addWidget(cpp14::make_unique<WBreak>());
                            container->setAttributeValue(Style::dataoid,val->view()["_id"].get_oid().value.to_string());
                            auto btn = container->addWidget(cpp14::make_unique<WPushButton>("Ekle"));
                            btn->addStyleClass(Bootstrap::Button::Primary);

                            btn->clicked().connect([=](){

                                auto filter = document{};

                                try {
                                    filter.append(kvp("_id",bsoncxx::oid{container->attributeValue(Style::dataoid).toUTF8()})) ;
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> filter." << "_id :"<< e.what() << std::endl;
                                }

                                auto pushDoc = document{};

                                try {
                                    pushDoc.append(kvp("saat",QTime::currentTime().toString("hh:mm").toStdString())) ;
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> pushDoc." << "saat :"<< e.what() << std::endl;
                                }

                                try {
                                    pushDoc.append(kvp("julianDate",QDate::currentDate().toJulianDay())) ;
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> pushDoc." << "julianDate :"<< e.what() << std::endl;
                                }

                                try {
                                    pushDoc.append(kvp("yorum",textEdit->text().toUTF8())) ;
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> pushDoc." << "yorum :"<< e.what() << std::endl;
                                }

                                try {
                                    pushDoc.append(kvp("onay",false)) ;
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> pushDoc." << "onay :"<< e.what() << std::endl;
                                }

                                try {
                                    pushDoc.append(kvp("userid",this->getOid())) ;
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> pushDoc." << "useid :"<< e.what() << std::endl;
                                }

                                try {
                                    pushDoc.append(kvp("nick",this->nickname())) ;
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> pushDoc." << "nick :"<< e.what() << std::endl;
                                }


                                auto push = document{};

                                try {
                                    push.append(kvp("$push",make_document(kvp("comments",pushDoc)))) ;
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> push." << "$push :"<< e.what() << std::endl;
                                }



                                try {
                                    push.append(kvp("$set",make_document(kvp("updated",QDateTime::currentSecsSinceEpoch())))) ;
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> push." << "$set :"<< e.what() << std::endl;
                                }


                                try {
                                    auto upt = this->db()->collection("forum").update_one(filter.view(),push.view());

                                    if( upt )
                                    {
                                        if( upt.value().modified_count() )
                                        {
                                            this->initItemPage(container->attributeValue(Style::dataoid).toUTF8());
                                        }
                                    }

                                } catch (mongocxx::exception &e) {
                                    std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
                                }








                            });


                        }else{
                            auto text = container->addWidget(cpp14::make_unique<WText>("Cevap Yazabilmek için Giriş Yapınız"));

                        }


                    }



                    {
                        auto container = mContainerWidget->addWidget(cpp14::make_unique<WContainerWidget>());
                        container->setWidth(WLength("100%"));
                        container->setContentAlignment(AlignmentFlag::Center);
                        auto btn = container->addWidget(cpp14::make_unique<WPushButton>("Geri"));
                        btn->addStyleClass(Bootstrap::Button::Primary);

                        btn->clicked().connect([=](){
                            this->initlistItem();
                        });
                    }


                }
            }else{
                this->ShowMessage("Uyarı","İçerik Görüntülenemiyor");
            }

        } catch (mongocxx::exception &e) {
            std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
            this->ShowMessage("Hata", "Line: " + std::to_string(__LINE__) + " Func: " + __FUNCTION__ + "  ->" + e.what());
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


        girisBtn->clicked().connect([=](){


            auto filter = document{};

            try {
                filter.append(kvp("Tel",text->text().toUTF8())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> filter." << "Tel :"<< e.what() << std::endl;
            }

            try {
                filter.append(kvp("Şifre",text1->text().toUTF8())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> filter." << "Şifre :"<< e.what() << std::endl;
            }


            try {
                auto val = this->db()->collection("Users").find_one(filter.view());

                if( val )
                {
                    if( val.value().view().empty() )
                    {
                        this->ShowMessage("Hata","<p>Yanlış Bilgi Girişi</p>"
                                                  "<p>Bilgilerinizi Tekrar Kontrol Ediniz</p>");
                    }else{
                        mBody->setPersonelView(val.value());
                        this->setPersonelView(val.value());
                        this->initStartupPage();
                    }
                }

            } catch (mongocxx::exception &e) {
                std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
            }







            //            this->setPersonelView()
        });



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

        auto telnumber = vLatout->addWidget(cpp14::make_unique<WLineEdit>() , 1 , AlignmentFlag::Justify|AlignmentFlag::Middle );
        telnumber->setPlaceholderText("Telefon Numarası Giriniz");

        auto yas = vLatout->addWidget(cpp14::make_unique<WLineEdit>() , 1 , AlignmentFlag::Justify|AlignmentFlag::Middle );
        yas->setPlaceholderText("Yaşınızı Giriniz");


        auto uyeBtn = vLatout->addWidget(cpp14::make_unique<WPushButton>("Kaydet") , 1 , AlignmentFlag::Center|AlignmentFlag::Middle );
        uyeBtn->addStyleClass(Bootstrap::Button::Primary);


        uyeBtn->clicked().connect([=](){

            if( nickName->text().toUTF8().size() < 4 )
            {
                this->ShowMessage("Uyarı","<p><b>NickName</b></p>"
                                           "<p>4 Karakter Az Olamaz</p>");
                return;
            }

            if( namesurname->text().toUTF8().size() < 4 )
            {
                this->ShowMessage("Uyarı","<p><b>Ad-Soyad</b></p>"
                                           "<p>4 Karakter Az Olamaz</p>");
                return;
            }

            if( telnumber->text().toUTF8().size() == 11 )
            {


            }else{
                this->ShowMessage("Uyarı","<p><b>Telefon Numarası Hatalı</b></p>"
                                           "<p>Telefon Numarası 11 Haneli Olmak Zorunda</p>");
                return;
            }

            if( yas->text().toUTF8().size() < 2 )
            {
                this->ShowMessage("Uyarı","<p><b>Yaş</b></p>"
                                           "<p>Yaşınızı Girmediniz veya Yanlış Girdiniz</p>");
                return;
            }


            auto filter = document{};


            try {
                filter.append(kvp("nickname",nickName->text().toUTF8())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> filter." << "nickname :"<< e.what() << std::endl;
            }


            try {
                auto val = this->db()->collection("Users").count(filter.view());

                if( val )
                {
                    this->ShowMessage("Uyarı","Bu nickname sistem başka bir kullanıcı tarafından kullanılıyor");
                    return;
                }

            } catch (mongocxx::exception &e) {
                std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
                this->ShowMessage("Hata","Line: " + std::to_string(__LINE__) + " Func: " + __FUNCTION__ + "  ->" +e.what());
                return;
            }


            auto doc = document{};

            try {
                doc.append(kvp("Tel",telnumber->text().toUTF8())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "Tel :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("nickname",nickName->text().toUTF8())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "Tel :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("AdSoyad",namesurname->text().toUTF8())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "Tel :"<< e.what() << std::endl;
            }
            auto sifre = this->getRandomNumber( 10000 , 99999 );
            try {
                doc.append(kvp("Şifre",std::to_string(sifre))) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "Şifre :"<< e.what() << std::endl;
            }



            try {
                auto ins = this->db()->collection("Users").insert_one(doc.view());

                if( ins )
                {
                    if( ins.value().result().inserted_count() )
                    {
                        this->ShowMessage("Bilgi","Kaydınız Başarılı.");
                        this->initLoginPage();
                    }else{
                        this->ShowMessage("Uyarı","Kayıt Yapılamadı. Daha Sonra Tekrar Deneyiniz.");
                    }
                }else{
                    this->ShowMessage("Uyarı","Kayıt Yapılamadı. Daha Sonra Tekrar Deneyiniz.");
                }

            } catch (mongocxx::exception &e) {
                std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
            }



        });




    }
}

void TaraftarPage::initNewKonuPage()
{

    clear();

    auto rContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    rContainer->setMaximumSize(600,WLength::Auto);

    {
        auto container = rContainer->addWidget(cpp14::make_unique<YeniKonu>(this->db()));
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        container->ClickSave().connect([=](){

            auto doc = document{};

            try {
                doc.append(kvp("baslik",container->title())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "baslik :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("html",container->html())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "html :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("useid",this->getOid())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "useid :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("onay",false)) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "onay :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("julianDate",QDate::currentDate().toJulianDay())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "julianDate :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("saat",QTime::currentTime().toString("hh:mm").toStdString())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "epochSec :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("nick",this->nickname())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "nick :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("+oy",0)) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "+oy :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("-oy",0)) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "-oy :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("oysayisi",0)) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "oysayisi :"<< e.what() << std::endl;
            }

            try {
                doc.append(kvp("updated",QDateTime::currentSecsSinceEpoch())) ;
            } catch (bsoncxx::exception &e) {
                std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> doc." << "oysayisi :"<< e.what() << std::endl;
            }


            try {
                auto ins = this->db()->collection("forum").insert_one(doc.view());
                if( ins )
                {
                    if( ins.value().result().inserted_count() )
                    {
                        this->ShowMessage("Bilgi","Kayıt Başarılı. Onaylandıktan Sonra Yayınlanacak.");
                        this->initStartupPage();
                    }else{
                        this->ShowMessage("Uyarı","Kayıt Yapılamadı");
                    }
                }else{
                    this->ShowMessage("Uyarı","Kayıt Yapılamadı");
                }
            } catch (mongocxx::exception &e) {
                std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
                this->ShowMessage("Hata","Line: " + std::to_string(__LINE__) + " Func: " + __FUNCTION__ + "  ->" +e.what());
            }
        });
    }
}

void TaraftarPage::initlistItem()
{
    mContainerWidget->clear();

    auto filter = document{};

    // TODO: Kullanımda Açılacak. Deneme Amaaçlı Kapalı
    //        try {
    //            filter.append(kvp("onay",true)) ;
    //        } catch (bsoncxx::exception &e) {
    //            std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> filter." << "onay :"<< e.what() << std::endl;
    //        }


    mongocxx::options::find findOptions;

    auto sortDoc = document{};


    try {
        sortDoc.append(kvp("updated",-1)) ;
    } catch (bsoncxx::exception &e) {
        std::cout << "Line " << __LINE__ << " Func: " << __FUNCTION__ << "-> sortDoc." << "updated :"<< e.what() << std::endl;
    }


    //        findOptions.limit(12)
    findOptions.sort(sortDoc.view());


    try {

        auto cursor = this->db()->collection("forum").find(filter.view(),findOptions);

        for( auto doc : cursor )
        {
            auto item = mContainerWidget->addWidget(cpp14::make_unique<TaraftarItem>(this->db(),doc));
            item->addStyleClass(Bootstrap::Grid::container_fluid);
            item->ClickTaraftarItem().connect(this,&TaraftarPage::initItemPage);
        }
    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << " Func: " << __FUNCTION__ << "  ->" <<e.what() << std::endl;
    }

}
