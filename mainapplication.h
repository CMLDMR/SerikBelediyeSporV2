#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

#include "../url.h"

#include "mongocxx.h"

#include <mongocxx/client.hpp>

using namespace Wt;

class MainApplication : public WApplication
{
public:
    MainApplication(const WEnvironment& env);



    mongocxx::client *mClient;



};

#endif // MAINAPPLICATION_H
