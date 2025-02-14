QT       += core gui
QT += multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battle.cpp \
    battlestate.cpp \
    enemy.cpp \
    grid.cpp \
    loseoutcome.cpp \
    main.cpp \
    mainwindow.cpp \
    monster.cpp \
    setting.cpp \
    teamselectionstate.cpp \
    winoutcome.cpp

HEADERS += \
    battle.h \
    battlestate.h \
    enemy.h \
    grid.h \
    loseoutcome.h \
    mainwindow.h \
    monster.h \
    setting.h \
    teamselectionstate.h \
    winoutcome.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    TOS2_zh_TW.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    dataset.qrc

DISTFILES += \
    ../../../../../../../../setting \
    ../../../../../../OneDrive/TOS2/dataset/setting.png \
    ../../../setting.png





