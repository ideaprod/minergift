include(minergift.pri)

TEMPLATE = subdirs
CONFIG += ordered

OUTPUT_DIR = $$PWD/output

SUBDIRS += mglib

test.depends = mglib
ui.depends = mglib

SUBDIRS += test
SUBDIRS += ui
