#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>


using namespace Wt;

class MainApplication : public WApplication
{
public:
MainApplication(const WEnvironment& env);
};

#endif // MAINAPPLICATION_H
