#-------------------------------------------------
#
# Project created by QtCreator 2015-04-29T00:57:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Base
TEMPLATE = app

CONFIG   += console
CONFIG += c++11

INCLUDEPATH += /usr/lib/
INCLUDEPATH += /home/sd/boost_1_58_0/stage/lib/
LIBS += -L/home/sd/boost_1_58_0/stage/lib/ -lboost_thread
LIBS += -L/home/sd/boost_1_58_0/stage/lib/ -lpthread
LIBS += -L/home/sd/boost_1_58_0/stage/lib/ -lboost_system

SOURCES += main.cpp\
        mainwindow.cpp \
    basestationcore.cpp \
    BoostSerialPort/BSerialPort.cpp \
    basestationiface.cpp \
    Joystick/JoystickAdv/joystickadv.cpp \
    sonars.cpp \
    sonarsroutine.cpp \
    PPM/ppm.cpp \
    argparser.cpp

HEADERS  += mainwindow.h \
    basestationcore.h \
    BoostSerialPort/BSerialPort.h \
    basestationiface.h \
    mwtypes.h \
    Joystick/JoystickAdv/joystickadv.h \
    Joystick/JoystickAdv/joytypes.h \
    sonars.h \
    sonarsroutine.h \
    PPM/ppm.h \
    argparser.h

FORMS    += mainwindow.ui

QT += serialport
