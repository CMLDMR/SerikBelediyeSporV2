#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WBootstrapTheme.h>

#include "../url.h"

#include "mongocxx.h"

#include <mongocxx/client.hpp>

#include "src/header.h"
#include "src/body.h"
#include "src/footer.h"

using namespace Wt;

class MainApplication : public WApplication
{
public:
    MainApplication(const WEnvironment& env);


    ///
    /// \brief init
    /// initialization main page;
    void init();

private:
    ///
    /// \brief mClient
    /// Database Connection
    mongocxx::client *mClient;


    ///
    /// \brief db
    /// Database variable
    mongocxx::database db;



    ///
    /// \brief mHeader
    /// header of page
    Header* mHeader;

    ///
    /// \brief mBody
    /// Main Page
    Body* mBody;


    ///
    /// \brief mFooter
    /// Footer Page
    Footer::Footer* mFooter;


    ///
    /// \brief p_wtTheme
    /// Booststrap Theme
    std::shared_ptr<Wt::WBootstrapTheme> p_wtTheme;


};

#endif // MAINAPPLICATION_H
