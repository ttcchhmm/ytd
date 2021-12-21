#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QWebSocketServer>
#include "../media/player.h"

class WebSocketServer : public QObject {
    Q_OBJECT

    public:
        /**
         * Create a new WebSocketServer and starts it on the specified port.
         */
        WebSocketServer(Player *p, int port);

    private slots:
        /**
         * Used to setup a new connection to the server.
         */
        void onNewConnection();

        /**
         * Used to handle text requests.
         */
        void onTextMessage(QString message);

        /**
         * Used when a client is disconnected.
         */
        void onSocketDisconnected();

        /**
         * Used to update the clients when the player changed position.
         */
        void onPlayerPositionUpdate(qint64 position);

        /**
         * Send an update to all clients.
         */
        void updateClients();

    private:
        /**
         * Returns the current state of the player as a JSON string
         */
        QString getStateJson();

        QWebSocketServer *qtWS;
        QVector<QWebSocket*> clients;

        Player *player;
};

#endif // WEBSOCKETSERVER_H