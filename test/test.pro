include(../minergift.pri)

QT += gui testlib

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app
TARGET = testminergift

INCLUDEPATH += ../mglib ../ui
DEPENDPATH += $${INCLUDEPATH} # force rebuild if the headers change

LIBS += $${_UI_LIB}
PRE_TARGETDEPS += $${_UI_LIB}

LIBS += -L$$PROJECT_OUTPUT/ -lminergift

SOURCES += tst_xmrigconnectortest.cpp

win32 {
    QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($${FOLDER}/testminergift.exe) $${PROJECT_OUTPUT}
}

unix {
    QMAKE_POST_LINK += $$QMAKE_COPY $$TARGET $${PROJECT_OUTPUT}
}
