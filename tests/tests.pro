TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT       += sql

SOURCES += \
        main.cpp \
    app.cpp \
    db.cpp \
    ../usuario.cpp \
    ../planta.cpp \
    ../token.cpp \
    ../queja.cpp \
    ../favorito.cpp \
    ../basedatos.cpp

HEADERS += \
    app.h \
    db.h \
    ../usuario.h \
    ../planta.h \
    ../token.h \
    ../queja.h \
    ../favorito.h \
    ../basedatos.h

LIBS += -pthread -lz -lssl -lcrypto

