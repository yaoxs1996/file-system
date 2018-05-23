TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    buffer.cpp \
    control.cpp \
    inode.cpp \
    sector.cpp \
    superblock.cpp

HEADERS += \
    control.h \
    myinclude.h
