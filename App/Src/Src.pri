INCLUDEPATH += $$PWD \
    $$PWD/Common \
    $$PWD/Common/Widget \
    $$PWD/CTopsView \
    $$PWD/CContentWidget \
    $$PWD/CMenuBottom \
    $$PWD/CThread \

HEADERS += \
    $$PWD/CContentWidget/CContentWidget.h \
    $$PWD/CMenuBottom/CBottomBar.h \
    $$PWD/CThread/CDataCollectHandler.h \
    $$PWD/CThread/CTestHandler.h \
    $$PWD/CThread/CThread.h \
    $$PWD/CThread/IThreadHandler.h \
    $$PWD/CTopsView/CTopsView.h \
    $$PWD/Common/CSystemConfig.h \
    $$PWD/Common/CUiToolkit.h \
    $$PWD/Common/Global_Common.h \
    $$PWD/Common/ICommand.h \
    $$PWD/Common/SystemCommom.h \
    $$PWD/Common/Widget/CCommandButton.h \
    $$PWD/Common/Widget/CListWidget.h \
    $$PWD/Common/Widget/CShadowBottomWidget.h \
    $$PWD/Common/Widget/IWidgetCreator.h

SOURCES += \
    $$PWD/CContentWidget/CContentWidget.cpp \
    $$PWD/CMenuBottom/CBottomBar.cpp \
    $$PWD/CThread/CDataCollectHandler.cpp \
    $$PWD/CThread/CTestHandler.cpp \
    $$PWD/CThread/CThread.cpp \
    $$PWD/CThread/IThreadHandler.cpp \
    $$PWD/CTopsView/CTopsView.cpp \
    $$PWD/Common/CSystemConfig.cpp \
    $$PWD/Common/CUiToolkit.cpp \
    $$PWD/Common/ICommand.cpp \
    $$PWD/Common/Widget/CCommandButton.cpp \
    $$PWD/Common/Widget/CListWidget.cpp \
    $$PWD/Common/Widget/CShadowBottomWidget.cpp \
    $$PWD/Common/Widget/IWidgetCreator.cpp

FORMS += \
    $$PWD/CContentWidget/ContentWidget.ui \
    $$PWD/CTopsView/TopsView.ui
