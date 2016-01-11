QT          += core gui multimedia network sql widgets

TARGET      = $$qtLibraryTarget(cover-fetcher)
TEMPLATE    = lib

DEFINES += MIAM_PLUGIN

CONFIG  += dll c++11
CONFIG  += qtquickcompiler

# TODO: how to minimize hardcoded paths?
win32 {
    MiamPlayerBuildDirectory = C:\dev\Miam-Player-build\src\MiamPlayer
    CONFIG(debug, debug|release) {
	target.path = $$MiamPlayerBuildDirectory\debug\plugins
	LIBS += -Ldebug -lMiamCore
    }

    CONFIG(release, debug|release) {
	target.path = $$MiamPlayerBuildDirectory\release\plugins
	LIBS += -Lrelease -lMiamCore
    }
}
unix {
    MiamPlayerBuildDirectory = /home/mbach/Miam-Player-release
    target.path = $$MiamPlayerBuildDirectory/MiamPlayer/plugins
    LIBS += -L$$MiamPlayerBuildDirectory/MiamCore -lmiam-core
}

UI_DIR = $$PWD

INSTALLS += target

SOURCES += providers/amazonprovider.cpp \
    providers/musicbrainzprovider.cpp \
    providers/lastfmprovider.cpp \
    coverfetcherplugin.cpp \
    coverwidgetitemdelegate.cpp \
    fetchdialog.cpp

HEADERS += interfaces/basicplugin.h \
    interfaces/itemviewplugin.h \
    model/albumdao.h \
    model/artistdao.h \
    model/genericdao.h \
    model/playlistdao.h \
    model/selectedtracksmodel.h \
    model/sqldatabase.h \
    model/trackdao.h \
    model/yeardao.h \
    providers/amazonprovider.h \
    providers/coverartprovider.h \
    providers/lastfmprovider.h \
    providers/musicbrainzprovider.h \
    cover.h \
    coverfetcherplugin.h \
    coverwidgetitemdelegate.h \
    fetchdialog.h \
    filehelper.h \
    miamcore_global.h \
    settings.h

FORMS += config.ui \
    fetchdialog.ui \
    templateCover.ui

TRANSLATIONS += translations/CoverFetcher_ar.ts \
    translations/CoverFetcher_cs.ts \
    translations/CoverFetcher_de.ts \
    translations/CoverFetcher_en.ts \
    translations/CoverFetcher_es.ts \
    translations/CoverFetcher_fr.ts \
    translations/CoverFetcher_it.ts \
    translations/CoverFetcher_ja.ts \
    translations/CoverFetcher_kr.ts \
    translations/CoverFetcher_pt.ts \
    translations/CoverFetcher_ru.ts \
    translations/CoverFetcher_th.ts \
    translations/CoverFetcher_vn.ts \
    translations/CoverFetcher_zh.ts

RESOURCES += resources.qrc
