TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

win32: LIBS += -LC:/Users/Elieser/Downloads/SDL2-2.0.9/lib/x64/ -lSDL2

INCLUDEPATH += C:/Users/Elieser/Downloads/SDL2-2.0.9/include
DEPENDPATH += C:/Users/Elieser/Downloads/SDL2-2.0.9/include

win32: LIBS += -L$$PWD/../SDL2-2.0.10/i686-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../SDL2-2.0.10/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../SDL2-2.0.10/i686-w64-mingw32/include
