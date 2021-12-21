#ifndef MAIN_H
#define MAIN_H

#include <QByteArray>
#include <QString>

#include "media/player.h"
#include "websocket/websocketserver.h"

namespace Main {
    inline Player *player;
    inline WebSocketServer *server;
}

int main(int argc, char *argv[]);

#endif // MAIN_H