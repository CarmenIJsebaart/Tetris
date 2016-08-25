TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBS += -LC:/SFML/lib
LIBS += -LC:\SFML\bin

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += C:/SFML/include
INCLUDEPATH += C:/Boost/include

INCLUDEPATH += C:/Boost

RESOURCES +=
