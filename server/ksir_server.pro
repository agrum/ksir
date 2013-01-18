#-------------------------------------------------
#
# Project created by QtCreator 2012-12-27T10:29:38
#
#-------------------------------------------------

QT       += core xml network sql
QT       -= gui

TARGET = ksir
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += /home/agrum/Workspace/pomelog/src/include \
	/home/agrum/Workspace/ksir/common/include
LIBS += -L/home/agrum/Workspace/ksir/build_common/lib \
	-lksir_common \
	-L/home/agrum/Workspace/pomelog/build/lib \
	-lpomelog

SOURCES += main.cpp \
	kserver.cpp \
    utils/kdatabase.cpp \
    utils/ktcpserver.cpp

HEADERS += kserver.h \
    utils/kdatabase.h \
    utils/ktcpserver.h

OTHER_FILES += \
    conf.d/serverlist.xml \
    conf.d/global1.xml \
    conf.d/global2.xml \
    conf.d/global3.xml
