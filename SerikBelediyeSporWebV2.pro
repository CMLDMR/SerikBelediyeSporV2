TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    mainapplication.cpp





win32: LIBS += -L$$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/lib/ -lwt

INCLUDEPATH += $$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/include
DEPENDPATH += $$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/include




win32: LIBS += -L$$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/lib/ -lwthttp

INCLUDEPATH += $$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/include
DEPENDPATH += $$PWD/../../Libraries/Wt-4.0.4-msvs2017-x64/include

HEADERS += \
    mainapplication.h \
    resource.h




win32: LIBS += -L$$PWD/mongo/lib/ -lbsoncxx

INCLUDEPATH += $$PWD/mongo/include/bsoncxx/v_noabi
DEPENDPATH += $$PWD/mongo/include/bsoncxx/v_noabi




win32: LIBS += -L$$PWD/mongo/lib/ -lmongocxx

INCLUDEPATH += $$PWD/mongo/include/mongocxx/v_noabi
DEPENDPATH += $$PWD/mongo/include/mongocxx/v_noabi
