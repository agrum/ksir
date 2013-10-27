#-------------------------------------------------
#
# Project created by QtCreator 2013-10-13T15:55:42
#
#-------------------------------------------------

QT       += core xml network
QT       -= gui

TARGET = ksir_game
TEMPLATE = lib

DEFINES += GAME_LIBRARY

SOURCES += game.cpp \
    territory.cpp \
    territoryeffect.cpp \
    region.cpp \
    cardterritory.cpp \
    cardevent.cpp \
    cardmission.cpp \
    worldmap.cpp \
    civilization.cpp \
    territorylink.cpp

HEADERS += game.h \
    territory.h \
    territoryeffect.h \
    region.h \
    deck.h \
    cardterritory.h \
    cardevent.h \
    cardmission.h \
    worldmap.h \
    civilization.h \
    territorylink.h

CONFIG(release, debug|release): LIBS += \
	-L$$PWD/../../pomelog/build/release/lib/ -lpomelog \
	-L$$PWD/../../ksir/build/release/lib/ -lksir_common
else:CONFIG(debug, debug|release): LIBS += \
	-L$$PWD/../../pomelog/build/release/lib/ -lpomelog \
	-L$$PWD/../../ksir/build/release/lib/ -lksir_common

INCLUDEPATH += \
	$$PWD/../common/include \
	$$PWD/../../pomelog/include
DEPENDPATH += \
	$$PWD/../common/include \
	$$PWD/../../pomelog/include
