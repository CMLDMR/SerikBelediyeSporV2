#include "mainapplication.h"

MainApplication::MainApplication(const WEnvironment &env)
    :WApplication (env)
{

    root()->addWidget(cpp14::make_unique<WText>("Serik Belediye Spor"));

}
