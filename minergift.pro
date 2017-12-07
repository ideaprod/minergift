 
TEMPLATE = subdirs
CONFIG += ordered


SUBDIRS += lib

test.depends = lib
ui.depends = lib

#SUBDIRS += test
SUBDIRS += ui
