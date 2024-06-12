QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GetPoints.cpp \
    Login.cpp \
    MapANDOptions.cpp \
    MySQL_Operate.cpp \
    Register.cpp \
    diaryall.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GetPoints.h \
    Login.h \
    MapANDOptions.h \
    MySQL_Operate.h \
    Register.h \
    diaryall.h \
    mainwindow.h

FORMS += \
    Login.ui \
    MapANDOptions.ui \
    Register.ui \
    diaryall.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
