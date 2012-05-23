#-------------------------------------------------
#
# Project created by QtCreator 2012-03-04T18:06:17
#
#-------------------------------------------------

QT       += core gui webkit network xml sql

CONFIG += console

TARGET = Switch
TEMPLATE = app


SOURCES += main.cpp\
        switch.cpp \
    googletalk.cpp \
    wlm.cpp \
    twitter.cpp \
    skype.cpp \
    facebook.cpp \
    manager.cpp

HEADERS  += switch.hpp \
    googletalk.hpp \
    lineedit.hpp \
    crypto.hpp \
    wlm.hpp \
    twitter.hpp \
    skype.hpp \
    facebook.hpp \
    manager.hpp
