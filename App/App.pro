QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FrameDemo
TEMPLATE = app
CONFIG += c++11

include($$PWD/Src/Src.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
HEADERS += \
    CAppSystem.h \
    CMainWindow.h \
    CStyleLoader.h

SOURCES += \
    CMainWindow.cpp \
    CStyleLoader.cpp \
    main.cpp \
    CAppSystem.cpp \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bin/config/systemconfig.xml

RESOURCES += \
    Qss.qrc
