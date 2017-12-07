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

#HEADERS_PUBLIC += \
#    minerapi.h

#target.path = $${PROJECT_OUTPUT}
#headerspub.files = $$HEADERS_PUBLIC
#headerspub.path = $${PROJECT_OUTPUT}

#message("EMILIEN $$OUT_PWD")

QMAKE_POST_LINK += if [ ! -d $${PROJECT_OUTPUT} ];then mkdir $${PROJECT_OUTPUT} ;fi && cp libminergift.so $${PROJECT_OUTPUT} && ln -fs $${PROJECT_OUTPUT}/libminergift.so $${PROJECT_OUTPUT}/libminergift.so.1
