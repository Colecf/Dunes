#-------------------------------------------------
#
# Project created by QtCreator 2017-10-10T15:40:21
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dunes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, `uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        modulelistitem.cpp \
    blockarea.cpp \
    modulelist.cpp \
    passdata.cpp \
    modules/scopemodule.cpp \
    modules/basemodule.cpp \
    modules/downloadmodule.cpp \
    modules/selectmodule.cpp \
    modules/gettextmodule.cpp \
    modules/nextmodule.cpp \
    modules/addrowmodule.cpp \
    modules/addcolumnmodule.cpp \
    modules/getparentmodule.cpp \
    modules/foreachmodule.cpp \
    modules/getattributemodule.cpp \
    codegen.cpp \
    modules/ifmodule.cpp \
    modules/whilemodule.cpp \
    modules/constantmodule.cpp \
    optionsmenu.cpp \
    existingfiledialog.cpp

HEADERS += \
        mainwindow.h \
    modulelistitem.h \
    blockarea.h \
    modulelist.h \
    passdata.h \
    modules/scopemodule.h \
    modules/basemodule.h \
    modules/downloadmodule.h \
    modules/selectmodule.h \
    modules/gettextmodule.h \
    modules/nextmodule.h \
    modules/addrowmodule.h \
    modules/addcolumnmodule.h \
    modules/getparentmodule.h \
    modules/foreachmodule.h \
    modules/getattributemodule.h \
    codegen.h \
    modules/ifmodule.h \
    modules/whilemodule.h \
    modules/constantmodule.h \
    optionsmenu.h \
    existingfiledialog.h

FORMS +=
