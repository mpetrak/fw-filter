# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist
TARGET = fw-filter
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui
SOURCES += lib/RulesXML.cpp lib/RulesPusher.cpp model/FilterRulesModel.cpp test/newForm.cpp view/MainWindow.cpp model/FilterRule.cpp lib/NetInterfaces.cpp view/LogView.cpp controller/main.cpp lib/OptionsLoader.cpp view/SettingsDialog.cpp view/RuleEditWidget.cpp lib/Logger.cpp
HEADERS += lib/Logger.h view/MainWindow.h test/newForm.h lib/OptionsLoader.h lib/RulesPusher.h view/SettingsDialog.h view/RuleEditWidget.h model/FilterRulesModel.h lib/RulesXML.h view/LogView.h model/FilterRule.h lib/NetInterfaces.h
FORMS += test/newForm.ui view/MainWindow.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += -Wl,-rpath,/usr/lib /usr/lib/libxml2.so  
