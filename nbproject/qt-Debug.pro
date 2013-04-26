# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = .
TARGET = fw-filter
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui
SOURCES += lib/RulesStatsLoader.cpp view/NegationComboBox.cpp view/NfOutputDialog.cpp lib/Configuration.cpp lib/RulesPusher.cpp lib/RulesXML.cpp model/FilterRulesModel.cpp view/MainWindow.cpp model/FilterRule.cpp lib/NetInterfaces.cpp view/LogView.cpp controller/main.cpp lib/OptionsLoader.cpp view/SettingsDialog.cpp view/RuleEditWidget.cpp lib/Logger.cpp view/StatisticsDialog.cpp view/MaskLineEdit.cpp
HEADERS += view/NfOutputDialog.h lib/Logger.h view/MainWindow.h lib/RulesStatsLoader.h view/NegationComboBox.h view/MaskLineEdit.h lib/OptionsLoader.h lib/RulesPusher.h lib/Configuration.h view/SettingsDialog.h view/RuleEditWidget.h model/FilterRulesModel.h lib/RulesXML.h view/LogView.h model/FilterRule.h lib/NetInterfaces.h view/StatisticsDialog.h
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
LIBS += -Wl,-rpath,/usr/lib /usr/lib/libxml2.so  
