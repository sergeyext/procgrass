#-------------------------------------------------
#
# Project created by QtCreator 2016-08-05T15:47:06
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = procgrass
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    viewport.cpp \
    shaderprogram.cpp \
    proceduralgrass.cpp \
    controlpanel.cpp

HEADERS  += mainwindow.h \
    viewport.h \
    fpvcamera.h \
    shaderprogram.h \
    proceduralgrass.h \
    controlpanel.h

FORMS    += mainwindow.ui \
    viewport.ui \
    controlpanel.ui

OTHER_FILES += \
    tree.vsh \
    tree.fsh \
    tree.gsh \
    tree.tcs \
    tree.tes \
    grass.tcs \
    grass.tes \
    grass.fsh \
    grass.gsh \
    grass.vsh \
    shared.glsl \
    classicnoise2D.glsl \
    classicnoise3D.glsl \
    worley.glsl \
