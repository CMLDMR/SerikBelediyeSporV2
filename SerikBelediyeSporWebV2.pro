TEMPLATE = app
CONFIG += console
CONFIG += c++1z
CONFIG -= app_bundle
#CONFIG -= qt

QT  += core
CONFIG += no_keywords

SOURCES += \
        main.cpp \
    mainapplication.cpp \
    src/containerwidget.cpp \
    src/header.cpp \
    src/body.cpp \
    src/slider.cpp \
    src/haberduyurucaps.cpp \
    src/takimlarwidget.cpp \
    src/footer.cpp \
    src/fotovideowidget.cpp \
    src/iletisimwidget.cpp \
    src/haberdetail.cpp \
    src/kurumsalpage.cpp



#QMAKE_CXXFLAGS += -Wunused-function






win32: LIBS += -L$$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/lib/ -lwt

INCLUDEPATH += $$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/include
DEPENDPATH += $$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/include




win32: LIBS += -L$$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/lib/ -lwthttp

INCLUDEPATH += $$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/include
DEPENDPATH += $$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/include

HEADERS += \
    mainapplication.h \
    resource.h \
    ../url.h \
    mongocxx.h \
    ../../Comman/bootstrap.h \
    ../../Comman/inlinestyle.h \
    src/containerwidget.h \
    src/header.h \
    src/body.h \
    src/slider.h \
    src/haberduyurucaps.h \
    src/takimlarwidget.h \
    src/footer.h \
    src/fotovideowidget.h \
    src/iletisimwidget.h \
    src/haberdetail.h \
    src/kurumsalpage.h

INCLUDEPATH += $$PWD/../../Comman
DEPENDPATH += $$PWD/../../Comman


win32: LIBS += -L$$PWD/mongo/lib/ -lbsoncxx

INCLUDEPATH += $$PWD/mongo/include/bsoncxx/v_noabi
DEPENDPATH += $$PWD/mongo/include/bsoncxx/v_noabi




win32: LIBS += -L$$PWD/mongo/lib/ -lmongocxx


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/mongo/lib/ -lmongocxx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/mongo/lib/ -lmongocxxd
else:unix: LIBS += -L$$PWD/mongo/lib/ -lmongocxx

INCLUDEPATH += $$PWD/mongo/include/mongocxx/v_noabi
DEPENDPATH += $$PWD/mongo/include/mongocxx/v_noabi





#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../Libraries/Boost MSVC 2015 x64/boost_1_68_0/lib64-msvc-14.0/' -lboost_atomic-vc140-mt-gd-x64-1_68
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../Libraries/Boost MSVC 2015 x64/boost_1_68_0/lib64-msvc-14.0/' -lboost_atomic-vc140-mt-gd-x64-1_68d

INCLUDEPATH += $$PWD/'../../Libraries/Boost MSVC 2015 x64/boost_1_68_0'
DEPENDPATH += $$PWD/'../../Libraries/Boost MSVC 2015 x64/boost_1_68_0'

DISTFILES += \
    ../build-SerikBelediyeSporWebV2-Desktop_Qt_5_12_0_MSVC2017_64bit3-Release/docroot/css/slider.css \
    ../build-SerikBelediyeSporWebV2-Desktop_Qt_5_12_0_MSVC2017_64bit3-Release/docroot/css/header.css
