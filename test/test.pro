include(../minergift.pri)

QT += gui testlib

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app
TARGET = testminergift

INCLUDEPATH += ../mglib

LIBS += -L$$PROJECT_OUTPUT/ -lminergift

SOURCES += tst_xmrigconnectortest.cpp

QMAKE_POST_LINK += $$QMAKE_COPY $$TARGET $${PROJECT_OUTPUT}
