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
    worlmap.cpp \
    territory.cpp \
    territoryeffect.cpp \
    region.cpp \
    player.cpp \
    actionlist.cpp \
    deck.cpp \
    cardterritory.cpp \
    cardevent.cpp \
    cardmission.cpp

HEADERS += game.h \
    worlmap.h \
    territory.h \
    territoryeffect.h \
    region.h \
    player.h \
    actionlist.h \
    card.h \
    deck.h \
    cardterritory.h \
    cardevent.h \
    cardmission.h

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
