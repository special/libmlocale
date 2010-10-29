include(../common_top.pri)
TARGET = ut_mapplicationmenu


INCLUDEPATH += $$MSRCDIR/corelib/widgets \
               $$MSRCDIR/corelib/style \
               $$MSRCDIR/scene \
               $$MSRCDIR/views

SOURCES += \
    ut_mapplicationmenu.cpp \
    $$MSRCDIR/views/mapplicationmenuview.cpp

HEADERS += \
    ut_mapplicationmenu.h

include(../common_bot.pri)
