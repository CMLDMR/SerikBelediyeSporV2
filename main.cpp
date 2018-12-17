#include <iostream>
#include <mongocxx/instance.hpp>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>

#include <Wt/WResource.h>
#include <Wt/WServer.h>
#include "resource.h"

#include "mainapplication.h"



//https://demo.joomdev.com/fitness/toolbar/

using namespace std;
using namespace Wt;



std::unique_ptr<WApplication> createApplication(const WEnvironment& env)
{
    auto app = Wt::cpp14::make_unique<MainApplication>(env);
    app->setTitle("Serik Belediye Spor Environment @ ");
    return std::move(app);
}



int main()
{
    cout << "Start up Serik Belediye Spor Web Application 2018" << endl;

    mongocxx::instance ins{};



    int argc = 6;
    auto argv = std::unique_ptr<char*[]>(new char*[argc]);

    //--docroot docroot --http-address 192.168.0.31 --http-port 8085 --approot approot --config approot/wt_config.xml
    argv[0] =  (char*)"SerikBelediyeSporWebV2";
    argv[1] =  (char*)"--http-address=192.168.0.31";
    argv[2] =  (char*)"--http-port=8084";

    argv[3] =  (char*)"--docroot=docroot";
    argv[4] =  (char*)"--approot=approot";
    argv[5] =  (char*)"--deploy-path=/";





    try {

        Wt::WServer server{argc, argv.get(), WTHTTP_CONFIGURATION};

//        Resource resource;

//        server.addResource(&resource, "/");
//        server.addResource(&resource, "/${test}");
//        server.addResource(&resource, "/users");
//        server.addResource(&resource, "/users/${user}");
//        server.addResource(&resource, "/users/${user}/posts");
//        server.addResource(&resource, "/users/${user}/posts/${post}");

        server.addEntryPoint(Wt::EntryPointType::Application, createApplication );




        //        server.addEntryPoint(EntryPointType::Application, [&](const Wt::WEnvironment &env) {
        //            return Wt::cpp14::make_unique<HelloApplication>(env,);
        //        } );



        if( server.start() ){
            auto sig = server.waitForShutdown();

            std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
            server.stop();


//            server.restart(argc, argv.get(),);

        }

//        server.run();



    } catch (const Wt::WServer::Exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (const std::exception &e) {
        std::cerr << "exception: " << e.what() << '\n';
        return 1;
    }


    return 0;
}
