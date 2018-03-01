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

win32 {
    SOURCES += \
        XmrigConnector/XmrigConnector.cpp \
        XmrigConnector/CpuLimiter.cpp \
        XmrigConnector/CpuLimitationThread.cpp

    HEADERS += \
        minerapi.h \
        XmrigConnector/XmrigConnector.h \
        XmrigConnector/CpuLimiter.h \
        XmrigConnector/CpuLimitationThread.h

    QMAKE_PRE_LINK += "( if not exist xmrig $$QMAKE_MKDIR xmrig ) \
                    & cd xmrig \
                    && cmake $$PWD/XmrigConnector/xmrig -G \"MinGW Makefiles\" -DUV_INCLUDE_DIR=\"C:/Program Files/libuv/include\" -DUV_LIBRARY=\"C:\Program Files\libuv\libuv.dll\" -DWITH_HTTPD=OFF \
                    && mingw32-make.exe -C $$OUT_PWD/xmrig"

    QMAKE_POST_LINK += "( if not exist $${PROJECT_OUTPUT} $$QMAKE_MKDIR $${PROJECT_OUTPUT} ) \
                    & $$QMAKE_COPY debug\minergift.dll $${PROJECT_OUTPUT} \
                    && $$QMAKE_COPY xmrig\xmrig.exe $${PROJECT_OUTPUT} \
                    && $$QMAKE_COPY $$shell_path($$PWD/XmrigConnector/libuv/libuv.dll) $${PROJECT_OUTPUT} "
}

unix {
    SOURCES += \
        XmrigConnector/XmrigConnector.cpp

    HEADERS += \
        minerapi.h \
        XmrigConnector/XmrigConnector.h

    QMAKE_PRE_LINK += $$QMAKE_MKDIR xmrig && cd xmrig && cmake $$PWD/XmrigConnector/xmrig -DWITH_HTTPD=OFF && make -C $$OUT_PWD/xmrig && cd $$PWD \
                    && $$QMAKE_MKDIR cpulimit && cd cpulimit && cd $$PWD/cpulimit/ && make

    QMAKE_POST_LINK += $$QMAKE_MKDIR $${PROJECT_OUTPUT} && $$QMAKE_COPY -P libminergift.so* \
                    $$PWD/cpulimit/src/cpulimit \
                    xmrig/xmrig \
                    $${PROJECT_OUTPUT}
}




