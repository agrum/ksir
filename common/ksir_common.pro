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

SOURCES += utils/kxmlbehavior.cpp \
	core/kcore.cpp \
	core/kmsg.cpp \
	core/kmsgheader.cpp \
	core/kdistant.cpp \
	utils/kcrypt.cpp \
    core/kcomlink.cpp \
    utils/kthread.cpp \
    core/kmailman.cpp \
    core/ksender.cpp \
    core/kreceiver.cpp

HEADERS += utils/kxmlbehavior.h \
	core/kcore.h \
	core/kmsg.h \
	core/kmsgheader.h \
	core/kdistant.h \
	include/ksir_common.h \
	utils/kcrypt.h \
    core/kcomlink.h \
    utils/kthread.h \
    core/kmailman.h \
    core/ksender.h \
    core/kreceiver.h

OTHER_FILES += \
    conf.d/serverlist.xml
