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

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    utils/string.cpp \
    utils/crypt.cpp \
    utils/msg.cpp \
    utils/xmlbehavior.cpp \
    core/distant.cpp \
    core/mailman.cpp \
    core/receiver.cpp \
    core/sender.cpp \
    core/comlink.cpp

HEADERS += \
	include/ksir_common.h \
    utils/prc.h \
    utils/string.h \
    utils/crypt.h \
    utils/msg.h \
    utils/xmlbehavior.h \
    utils/prc.h \
    core/distant.h \
    core/mailman.h \
    core/receiver.h \
    core/sender.h \
    core/comlink.h

OTHER_FILES += \
	conf.d/serverlist.xml

CONFIG(release, debug|release): LIBS += -L$$PWD/../../pomelog/build/release/lib/ -lpomelog
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../pomelog/build/debug/lib/ -lpomelog

INCLUDEPATH += $$PWD/../../pomelog/include
DEPENDPATH += $$PWD/../../pomelog/include
