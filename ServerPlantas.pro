TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    planta.cpp

LIBS += -pthread -lz

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../websocket/lib/release/ -lixwebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../websocket/lib/debug/ -lixwebsocket
else:unix: LIBS += -L$$PWD/../../websocket/lib/ -lixwebsocket

INCLUDEPATH += $$PWD/../../websocket/include
DEPENDPATH += $$PWD/../../websocket/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/lib/release/libixwebsocket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/lib/debug/libixwebsocket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/lib/release/ixwebsocket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/lib/debug/ixwebsocket.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../websocket/lib/libixwebsocket.a

HEADERS += \
    planta.h
