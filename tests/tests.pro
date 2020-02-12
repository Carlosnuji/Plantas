TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT       += sql

SOURCES += \
        main.cpp \
    app.cpp \
    db.cpp

HEADERS += \
    app.h \
    db.h
