TEMPLATE = app
CONFIG += console c++11 qt
CONFIG -= app_bundle

QT       += sql

SOURCES += \
        main.cpp \
    planta.cpp \
    servidor.cpp \
    conexion.cpp

LIBS += -pthread -lz



HEADERS += \
    planta.h \
    servidor.h \
    conexion.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../webSocket/lib/release/ -lixwebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../webSocket/lib/debug/ -lixwebsocket
else:unix: LIBS += -L$$PWD/../../webSocket/lib/ -lixwebsocket

INCLUDEPATH += $$PWD/../../webSocket/include
DEPENDPATH += $$PWD/../../webSocket/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../webSocket/lib/release/libixwebsocket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../webSocket/lib/debug/libixwebsocket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../webSocket/lib/release/ixwebsocket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../webSocket/lib/debug/ixwebsocket.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../webSocket/lib/libixwebsocket.a
