#-------------------------------------------------
#
# Project created by QtCreator 2012-12-27T10:29:38
#
#-------------------------------------------------

QT       += core xml network
QT       -= gui

TARGET = ksir_common

TEMPLATE = lib
DESTDIR = lib

INCLUDEPATH += ../../pomelog/src/include
LIBS += -L../../pomelog/build-pomelog-Desktop-Release/lib \
        -lpomelog

SOURCES += \
	core/kdistant.cpp \
    core/kmailman.cpp \
    core/ksender.cpp \
    core/kreceiver.cpp \
    utils/string.cpp \
    utils/comlink.cpp \
    utils/crypt.cpp \
    utils/msg.cpp \
    utils/msginner.cpp \
    utils/xmlbehavior.cpp \
    utils/msgoutter.cpp

HEADERS += \
	core/kdistant.h \
	include/ksir_common.h \
    core/kmailman.h \
    core/ksender.h \
    core/kreceiver.h \
    utils/prc.h \
    utils/string.h \
    utils/comlink.h \
    utils/crypt.h \
    utils/msginner.h \
    utils/msg.h \
    utils/msgoutter.h \
    utils/xmlbehavior.h \
    utils/prc.h

OTHER_FILES += \
    conf.d/serverlist.xml
