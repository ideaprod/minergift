include(../minergift.pri)

TEMPLATE = lib
TARGET = minergift

QT += core

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    XmrigConnector/XmrigConnector.cpp

HEADERS += \
    minerapi.h \
    XmrigConnector/XmrigConnector.h

QMAKE_PRE_LINK += $$QMAKE_MKDIR xmrig && cd xmrig && cmake $$PWD/XmrigConnector/xmrig -DWITH_HTTPD=OFF && make -C $$OUT_PWD/xmrig

QMAKE_POST_LINK += $$QMAKE_MKDIR $${PROJECT_OUTPUT} && $$QMAKE_COPY -P libminergift.so* xmrig/xmrig $${PROJECT_OUTPUT}
