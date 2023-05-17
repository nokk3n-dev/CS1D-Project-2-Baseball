QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminlogin.cpp \
    adminoptions.cpp \
    dbhandler.cpp \
    global.cpp \
    kruskal.cpp \
    main.cpp \
    mainwindow.cpp \
    planningtourpage.cpp \
    prims.cpp \
    souvenir.cpp \
    team.cpp \
    unordermap.cpp \
    viewingpage.cpp

HEADERS += \
    adminlogin.h \
    adminoptions.h \
    dbConstance.h \
    dbhandler.h \
    global.h \
    kruskal.h \
    mainwindow.h \
    planningtourpage.h \
    prims.h \
    souvenir.h \
    team.h \
    teamList.h \
    unorderedmap.h \
    viewingpage.h

FORMS += \
    adminlogin.ui \
    adminoptions.ui \
    dialog.ui \
    kruskal.ui \
    mainwindow.ui \
    planningtourpage.ui \
    prims.ui \
    viewingpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
