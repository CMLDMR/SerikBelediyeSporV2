#include "mainapplication.h"
#include <Wt/WOverlayLoadingIndicator.h>

MainApplication::MainApplication(const WEnvironment &env)
    :WApplication (env)
{

    wApp->addMetaHeader(MetaHeaderType::Meta,"Content-Type","text/html; charset=utf-8");

    setTitle("Serik Belediye Spor Resmi Web Sayfası");

    try {
        mClient = new mongocxx::client(mongocxx::uri(_url));
    } catch (mongocxx::exception& e) {
        std::cout << "MongoDB Connection Error: " << e.what() << std::endl;
        root()->addWidget(cpp14::make_unique<WText>("Driver Yüklenemedi!"));
        return;
    } catch ( ... )
    {
        std::cout << "uknown Error Mongocxx Connection" << std::endl;
    }


    db = mClient->database("SerikSpor");


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
    Wt::WApplication::instance()->useStyleSheet("css/header.css");
    WApplication::instance()->addMetaHeader("viewport","width=device-width, initial-scale=1.0");


//    std::cout << "Size: " << env.getParameterMap().size() << std::endl;


    auto map = env.getParameterMap();
    std::string link = "";
    for( auto item : map )
    {
        if( item.second.size() ){
            link = item.second.at(0);
        }
    }


    this->init();

    if( link.size() )
    {
        this->initRequestedItem(link);
    }








}

void MainApplication::init()
{

    mHeader = root()->addWidget(cpp14::make_unique<Header>(&db));

    mBody = root()->addWidget(cpp14::make_unique<Body>(&db));

    mFooter = root()->addWidget(cpp14::make_unique<Footer::Footer>());
}

void MainApplication::initRequestedItem(std::string url_)
{


    QString url = QString::fromStdString(url_);



    if( url.at(0) == "/" )
    {
        url.remove(0,1);
    }
    std::string collection;
    std::string oid;

    int counter = 1;
    for( auto item : url.split("&") ){
        if( counter == 1 )
        {
            collection = item.split("=").last().toStdString();
        }

        if( counter == 2 )
        {
            if( item.split("=").first() == "oid" )
            {
                if( collection == "Haberler" )
                {
                    this->mBody->initDirectHaber(item.split("=").last().toStdString() );
                    break;
                }
            }
        }
        counter++;
    }

}
