#include "mainapplication.h"
#include <Wt/WOverlayLoadingIndicator.h>

MainApplication::MainApplication(const WEnvironment &env)
    :WApplication (env)
{

    wApp->addMetaHeader(MetaHeaderType::Meta,"Content-Type","text/html; charset=utf-8");

    setTitle("Serik Belediye Spor Resmi Web Sayfası");

//    try {
//        mClient = new mongocxx::client(mongocxx::uri(_url));
//    } catch (mongocxx::exception& e) {
//        std::cout << "MongoDB Connection Error: " << e.what() << std::endl;
//        root()->addWidget(cpp14::make_unique<WText>("Driver Yüklenemedi!"));
//        return;
//    } catch ( ... )
//    {
//        std::cout << "uknown Error Mongocxx Connection" << std::endl;
//    }


//    db = mClient->database("SERIKBELEDIYESPORV2");


    Wt::WApplication *app = Wt::WApplication::instance();
    app->setLoadingIndicator(std::make_unique<WOverlayLoadingIndicator>());
    app->loadingIndicator()->setMessage("Yükleniyor...");


    p_wtTheme = std::make_shared<Wt::WBootstrapTheme>();

    p_wtTheme->setVersion(Wt::WBootstrapTheme::Version::v3);

    p_wtTheme.get()->setResponsive(true);

    Wt::WApplication::instance()->setTheme(p_wtTheme);

    Wt::WApplication::instance()->setTitle("Serik Belediyesi Resmi Web Sayfası");
    Wt::WApplication::instance()->addMetaLink("icon/20180126113337667.ico","shortcut icon","","","image/x-icon","16x16",false);


    Wt::WApplication::instance()->useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");
    Wt::WApplication::instance()->useStyleSheet("css/slider.css");
    WApplication::instance()->addMetaHeader("viewport","width=device-width, initial-scale=1.0");


    auto filter = document{};


//    try {
//        auto cursor = mClient->database("SERIKBELEDIYESPORV2").collection("test").find(document{}.view());

//        for( auto item : cursor )
//        {
//            std::cout << item["test"].get_utf8().value.to_string() << std::endl;
//        }

//    } catch (mongocxx::exception &e) {
//        std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
//    }


    this->init();


}

void MainApplication::init()
{

    mHeader = root()->addWidget(cpp14::make_unique<Header>(&db));

    mBody = root()->addWidget(cpp14::make_unique<Body>(&db));

    mFooter = root()->addWidget(cpp14::make_unique<Footer::Footer>());


}
