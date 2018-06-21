include(../minergift.pri)

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = uiminergift
RESOURCES = uiminergift.qrc
CONF = miner.json

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../mglib

LIBS += -L$$PROJECT_OUTPUT/ -lminergift

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    conf.cpp

HEADERS += \
    mainwindow.h \
    constants.h \
    conf.h

FORMS += mainwindow.ui

win32 {
	!isEmpty(IS_LINUX){
               QMAKE_POST_LINK += "if [ ! -f $$shell_path($$OUT_PWD/../output/$$CONF) ]; then $$QMAKE_COPY $$shell_path($$PWD/$$CONF) $${PROJECT_OUTPUT}; fi \
                && $$QMAKE_COPY $${FOLDER}/uiminergift.exe $${PROJECT_OUTPUT} "
	}
	!isEmpty(IS_WIN){
               QMAKE_POST_LINK += "( if not exist $$shell_path($$OUT_PWD/../output/$$CONF) $$QMAKE_COPY $$shell_path($$PWD/$$CONF) $${PROJECT_OUTPUT} ) \
                    & $$QMAKE_COPY $${FOLDER}\uiminergift.exe $${PROJECT_OUTPUT} "
	}
}

unix {
    QMAKE_POST_LINK += "if [ ! -f $$shell_path($$OUT_PWD/../output/$$CONF) ]; then $$QMAKE_COPY $$shell_path($$PWD/$$CONF) $${PROJECT_OUTPUT}; fi \
                    && $$QMAKE_COPY $$TARGET $${PROJECT_OUTPUT} "
}
