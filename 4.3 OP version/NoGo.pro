QT       += core gui
QT       += core
#QT       += multimedia
QT       += multimedia
QT       += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    item.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow_01.cpp \
    yonghu.cpp

HEADERS += \
    item.h \
    mainwindow.h \
    mainwindow_01.h \
    yonghu.h

FORMS += \
    mainwindow.ui \
    mainwindow_01.ui \
    yonghu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    BGM.qrc \
    WAV.qrc \
    button.qrc \
    giveup.qrc \
    leishen.qrc \
    leishen2.qrc \
    mikubcg.qrc \
    newback.qrc \
    pic.qrc \
    restart.qrc \
    restart.qrc \
    result.qrc \
    start.qrc \
    start.qrc \
    time.qrc \
    zhenghuo.qrc \
    zhongli.qrc

DISTFILES += \
    image/help.png \
    image/login.png \
    image/ourteam.png \
    image/visitor.png
