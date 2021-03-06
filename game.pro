TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}
LIBS += -lOpenGL32 -lglu32

SOURCES += \
        Character.cpp \
        camera.cpp \
        collision.cpp \
        main.cpp \
        menu.cpp \
        network.cpp \
        sound.cpp \
        world.cpp


HEADERS += \
    Character.h \
    menu.h \
    network.h \
    sound.h \
    world.h

