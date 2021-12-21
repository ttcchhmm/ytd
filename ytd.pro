QT -= gui widgets
QT += multimedia websockets

CONFIG += c++20 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES = main.cpp yt-dl/ytdl.cpp cachemanager/cachemanager.cpp media/media.cpp media/player.cpp websocket/websocketserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS = yt-dl/ytdl.h console/console.h cachemanager/cachemanager.h media/media.h media/player.h websocket/websocketserver.h