QT          += core gui multimedia network sql widgets

TARGET      = $$qtLibraryTarget(cover-fetcher)
TEMPLATE    = lib

MiamPlayerBuildDirectory = C:\dev\Miam-Player-build-x64\MiamPlayer

DEFINES += MIAM_PLUGIN

CONFIG  += dll c++11
CONFIG(debug, debug|release) {
    target.path = $$MiamPlayerBuildDirectory\debug\plugins
    LIBS += -Ldebug -lMiamCore
}

CONFIG(release, debug|release) {
    target.path = $$MiamPlayerBuildDirectory\release\plugins
    LIBS += -Lrelease -lMiamCore
}

UI_DIR = $$PWD

INSTALLS += target

SOURCES += \
    itemviewplugin.cpp \
    coverfetcher.cpp \
    fetchdialog.cpp \
    coverwidgetitemdelegate.cpp

HEADERS += \
    model/librarysqlmodel.h \
    model/selectedtracksmodel.h \
    basicplugininterface.h \
    cover.h \
    coverfetcher.h \
    coverwidgetitemdelegate.h \
    fetchdialog.h \
    filehelper.h \
    itemviewplugin.h \
    itemviewplugininterface.h \
    mediaplayerplugininterface.h \
    miamcore_global.h \
    settings.h \
    sqldatabase.h

FORMS += \
    fetchdialog.ui \
    templateCover.ui \
    config.ui
