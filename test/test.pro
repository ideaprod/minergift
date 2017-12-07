include(../minergift.pri)

QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app
TARGET = testminergift

INCLUDEPATH += ../mglib

LIBS += -L$$PROJECT_OUTPUT/ -lminergift

SOURCES += \ 
    tst_xmrigconnectortest.cpp
