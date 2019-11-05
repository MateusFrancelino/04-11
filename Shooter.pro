TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

win32: LIBS += -L$$PWD/../../SDL2-2.0.10/x86_64-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../SDL2-2.0.10/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/../../SDL2-2.0.10/x86_64-w64-mingw32/include
