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

INCLUDEPATH += /home/agrum/Workspace/pomelog/src/include
LIBS += -L/home/agrum/Workspace/pomelog/build/lib \
	-lpomelog \

SOURCES += utils/kxmlbehavior.cpp \
	core/kcore.cpp \
	core/kmsg.cpp \
	core/kmsgheader.cpp \
    core/kdistant.cpp \
    utils/kcommonlogextension.cpp

HEADERS += utils/kxmlbehavior.h \
	core/kcore.h \
	core/kmsg.h \
	core/kmsgheader.h \
    include/ksir_common.h \
    core/kdistant.h \
    utils/kcommonlogextension.h

OTHER_FILES += \
    conf.d/serverlist.xml
