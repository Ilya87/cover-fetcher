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
    fetchdialog.cpp

HEADERS += \
    basicplugininterface.h \
    miamcore_global.h \
    itemviewplugininterface.h \
    itemviewplugin.h \
    coverfetcher.h \
    librarysqlmodel.h \
    filehelper.h \
    mediaplayerplugininterface.h \
    sqldatabase.h \
    fetchdialog.h \
    settings.h

FORMS += \
    fetchdialog.ui \
    templateCover.ui
