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
    allclass.cpp \
    bupt.cpp \
    changepassword.cpp \
    changeusername.cpp \
    diaryall.cpp \
    diarydetail.cpp \
    main.cpp \
    mainwindow.cpp \
    mine.cpp \
    mydiary.cpp \
    mydiarydetail.cpp \
    uploaddiary.cpp

HEADERS += \
    GetPoints.h \
    Login.h \
    MapANDOptions.h \
    MySQL_Operate.h \
    Register.h \
    allclass.h \
    bupt.h \
    changepassword.h \
    changeusername.h \
    diaryall.h \
    diarydetail.h \
    mainwindow.h \
    mine.h \
    mydiary.h \
    mydiarydetail.h \
    uploaddiary.h

FORMS += \
    Login.ui \
    MapANDOptions.ui \
    Register.ui \
    bupt.ui \
    changepassword.ui \
    changeusername.ui \
    diaryall.ui \
    diarydetail.ui \
    mainwindow.ui \
    mine.ui \
    mydiary.ui \
    mydiarydetail.ui \
    uploaddiary.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
