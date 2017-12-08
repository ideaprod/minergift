
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += mglib

test.depends = mglib
ui.depends = mglib

SUBDIRS += test
SUBDIRS += ui
