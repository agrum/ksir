#-------------------------------------------------
#
# Project created by QtCreator 2012-12-27T10:29:38
#
#-------------------------------------------------

QT       += core xml network
QT       -= gui

TARGET = ksir
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += /home/agrum/Workspace/pomelog/include \
	/home/agrum/Workspace/ksir/common/include
LIBS += -L/home/agrum/Workspace/ksir/build_common/lib \
	-lksir_common \
	-L/home/agrum/Workspace/pomelog/lib \
	-lpomelog

SOURCES += main.cpp \
	kserver.cpp

HEADERS += kserver.h

OTHER_FILES += \
    conf.d/serverlist.conf \
    conf.d/global.conf
