TEMPLATE = app
CONFIG += console c++11 qt
CONFIG -= app_bundle

QT       += sql

SOURCES += \
        main.cpp \
    planta.cpp \
    servidor.cpp \
    conexion.cpp \
    usuario.cpp \
    queja.cpp \
    favorito.cpp

LIBS += -pthread -lz -lssl -lcrypto



HEADERS += \
    planta.h \
    servidor.h \
    conexion.h \
    usuario.h \
    queja.h \
    favorito.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/websocketLib/lib/release/ -lixwebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/websocketLib/lib/debug/ -lixwebsocket
else:unix: LIBS += -L$$PWD/websocketLib/lib/ -lixwebsocket

INCLUDEPATH += $$PWD/websocketLib/include
DEPENDPATH += $$PWD/websocketLib/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/websocketLib/lib/release/libixwebsocket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/websocketLib/lib/debug/libixwebsocket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/websocketLib/lib/release/ixwebsocket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/websocketLib/lib/debug/ixwebsocket.lib
else:unix: PRE_TARGETDEPS += $$PWD/websocketLib/lib/libixwebsocket.a
