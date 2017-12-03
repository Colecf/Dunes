#-------------------------------------------------
#
# Project created by QtCreator 2017-11-05T16:59:06
#
#-------------------------------------------------

QT       += core gui testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tst_unittesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../Dunes/
INCLUDEPATH += ../Dunes/modules

HEADERS += \
        ../Dunes/mainwindow.h \
   ../Dunes/modulelistitem.h \
   ../Dunes/blockarea.h \
   ../Dunes/modulelist.h \
   ../Dunes/modules/scopemodule.h \
   ../Dunes/modules/basemodule.h \
   ../Dunes/modules/downloadmodule.h \
   ../Dunes/modules/selectmodule.h \
   ../Dunes/modules/gettextmodule.h \
   ../Dunes/modules/nextmodule.h \
   ../Dunes/modules/addrowmodule.h \
   ../Dunes/modules/addcolumnmodule.h \
   ../Dunes/modules/foreachmodule.h \
   ../Dunes/modules/getattributemodule.h \
   ../Dunes/codegen.h \
   ../Dunes/modules/ifmodule.h \
   ../Dunes/modules/whilemodule.h \
   ../Dunes/modules/constantmodule.h \
   ../Dunes/optionsmenu.h \
   ../Dunes/existingfiledialog.h \
   ../Dunes/saveload.h \
   ../Dunes/modules/setvariablemodule.h \
   ../Dunes/modules/getvariablemodule.h \
   ../Dunes/testcasespy.h

SOURCES += \
        tst_unittesttest.cpp
SOURCES += \
    ../Dunes/mainwindow.cpp \
    ../Dunes/modulelistitem.cpp \
    ../Dunes/blockarea.cpp \
    ../Dunes/modulelist.cpp \
    ../Dunes/modules/scopemodule.cpp \
    ../Dunes/modules/basemodule.cpp \
    ../Dunes/modules/downloadmodule.cpp \
    ../Dunes/modules/selectmodule.cpp \
    ../Dunes/modules/gettextmodule.cpp \
    ../Dunes/modules/nextmodule.cpp \
    ../Dunes/modules/addrowmodule.cpp \
    ../Dunes/modules/addcolumnmodule.cpp \
    ../Dunes/modules/foreachmodule.cpp \
    ../Dunes/modules/getattributemodule.cpp \
    ../Dunes/codegen.cpp \
    ../Dunes/modules/ifmodule.cpp \
    ../Dunes/modules/whilemodule.cpp \
    ../Dunes/modules/constantmodule.cpp \
    ../Dunes/optionsmenu.cpp \
    ../Dunes/existingfiledialog.cpp \
    ../Dunes/saveload.cpp \
    ../Dunes/modules/setvariablemodule.cpp \
    ../Dunes/modules/getvariablemodule.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
