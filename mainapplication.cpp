#include "mainapplication.h"

MainApplication::MainApplication(const WEnvironment &env)
    :WApplication (env)
{

    root()->addWidget(cpp14::make_unique<WText>("Serik Belediye Spor"));


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



    auto filter = document{};


    try {
        auto cursor = mClient->database("SERIKBELEDIYESPORV2").collection("test").find(document{}.view());

        for( auto item : cursor )
        {
            std::cout << item["test"].get_utf8().value.to_string() << std::endl;
        }

    } catch (mongocxx::exception &e) {
        std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
    }


}
