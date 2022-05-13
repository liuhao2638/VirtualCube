QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../VirtualCube/VirtualCube

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainview.cpp \
    cube.cpp \
    frame.cpp \
    face.cpp \
    mainwindow.cpp \
    mainwidget.cpp \
    cubedata.cpp

HEADERS += \
    mainview.h \
    cube.h \
    frame.h \
    face.h \
    mainwindow.h \
    mainwidget.h \
    cubedata.h

win32: LIBS += -L$$PWD/assimp/lib/ -llibassimp.dll

INCLUDEPATH += $$PWD/assimp/include
DEPENDPATH += $$PWD/assimp/include

RC_ICONS = logo.ico
