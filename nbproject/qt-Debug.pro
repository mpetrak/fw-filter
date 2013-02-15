# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = fw-filter
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui
SOURCES += lib/RulesPusher.cpp model/FilterRulesModel.cpp view/MainWindow.cpp model/FilterRule.cpp lib/NetInterfaces.cpp lib/OptionsLoader.cpp controller/main.cpp view/RuleEditWidget.cpp
HEADERS += view/MainWindow.h lib/OptionsLoader.h lib/RulesPusher.h lib/Netfilter.h view/RuleEditWidget.h model/FilterRulesModel.h lib/NetInterfaces.h model/FilterRule.h
FORMS += view/MainWindow.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = qt
RCC_DIR = 
UI_DIR = qt
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
