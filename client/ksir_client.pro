#-------------------------------------------------
#
# Project created by QtCreator 2012-12-27T10:29:38
#
#-------------------------------------------------

QT       += core xml network sql
QT       += gui widgets

TARGET = ksir
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    kclient.cpp

HEADERS += \
		kclient.h

OTHER_FILES += \
    conf.d/global1.xml

FORMS +=

CONFIG(release, debug|release): LIBS += \
	-L$$PWD/../../pomelog/build/release/lib/ -lpomelog \
	-L$$PWD/../../ksir/build/release/lib/ -lksir_common
else:CONFIG(debug, debug|release): LIBS += \
	-L$$PWD/../../pomelog/build/debug/lib/ -lpomelog \
	-L$$PWD/../../ksir/build/debug/lib/ -lksir_common

INCLUDEPATH += $$PWD/../../pomelog/include
INCLUDEPATH += $$PWD/../../ksir/common/include
DEPENDPATH += $$PWD/../../pomelog/include
DEPENDPATH += $$PWD/../../ksir/common/include
