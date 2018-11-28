#ifndef RESOURCE_H
#define RESOURCE_H

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WEnvironment.h>

#include <Wt/WResource.h>
#include <Wt/WServer.h>

#include <Wt/Http/Request.h>
#include <Wt/Http/Response.h>

#include <iostream>

class Resource : public Wt::WResource {
public:

    Resource()
        : WResource()
    {

    }

    ~Resource() override {
        std::cout << "Being Deleted" << std::endl;
        beingDeleted();
    }


    virtual void handleRequest(const Wt::Http::Request &request,
                               Wt::Http::Response &response) override
    {

        std::cout << "Method: " << request.method() << std::endl;

        std::cout << request.urlParam("param1") << std::endl;

        for (;;) {
            std::string buffer;
            if (!std::getline(request.in(), buffer)) break;
            std::cout << "Got: '" << buffer << "'\n";
        }


        response.setMimeType("text/plain");

        response.out() << "Session id: " << this->id() << "\n";



        response.out() << "Request path:\n" << request.path() << "\n\n";


        this->setInternalPath(request.path()+"/"+request.pathInfo());

        auto pathInfo = request.pathInfo();
        if ( pathInfo.empty() )
            pathInfo = "(empty)";
        response.out() << "Request path info:\n" << pathInfo << "\n\n";

        response.out() << "Request URL parameters\n----------------------\n";

        auto params = request.urlParams();

        if ( params.empty() )
            response.out() << "(empty)\n";

        for (const auto &param : params) {
            const auto &name = param.first;
            const auto &value = param.second;
            response.out() << name << ": " << value << '\n';
        }
    }
};


#endif // RESOURCE_H
