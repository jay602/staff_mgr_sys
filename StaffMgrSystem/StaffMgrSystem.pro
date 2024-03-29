QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


DESTDIR = ./bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addclerkdialog.cpp \
    adduserdialog.cpp \
    attendancedialog.cpp \
    attendancesqlquerymodel.cpp \
    clerk.cpp \
    clerksqlquerymodel.cpp \
    clerkwidget.cpp \
    globle.cpp \
    logindialog.cpp \
    main.cpp \
    mainwidget.cpp \
    mainwindow.cpp \
    salarydialog.cpp \
    salarysqlquerymodel.cpp \
    sqlserver.cpp \
    uilog.cpp

HEADERS += \
    StData.h \
    addclerkdialog.h \
    adduserdialog.h \
    attendancedialog.h \
    attendancesqlquerymodel.h \
    clerk.h \
    clerksqlquerymodel.h \
    clerkwidget.h \
    globle.h \
    log.h \
    logindialog.h \
    mainwidget.h \
    mainwindow.h \
    salarydialog.h \
    salarysqlquerymodel.h \
    singleton.hpp \
    sqlserver.h \
    uilog.h

FORMS += \
    addclerkdialog.ui \
    adduserdialog.ui \
    attendancedialog.ui \
    clerkwidget.ui \
    logindialog.ui \
    mainwidget.ui \
    mainwindow.ui \
    salarydialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
