QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = slice-app
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    error.cpp

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    serror.h
