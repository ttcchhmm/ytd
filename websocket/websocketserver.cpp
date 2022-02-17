#include "websocketserver.h"

#include <QStringLiteral>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QHostAddress>
#include <QWebSocket>
#include <QMediaPlayer>
#include "../console/console.h"
#include "../yt-dl/ytdl.h"
#include "../media/media.h"

WebSocketServer::WebSocketServer(Player *p, int port) {
    player = p;
    qtWS = new QWebSocketServer(QStringLiteral("ytd Server"), QWebSocketServer::NonSecureMode, this);

    if (qtWS->listen(QHostAddress::Any, port)) {
        Console::out << "WebSocketServer ready on port " << port << Qt::endl;

        // WebSocket signals/slots
        connect(qtWS, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);

        // QMediaPlayer signals/slots
        connect(player->getQtMediaPlayer(), &QMediaPlayer::positionChanged, this, &WebSocketServer::onPlayerPositionUpdate);
        connect(player, &Player::stateUpdated, this, &WebSocketServer::updateClients);
    } else {
        Console::err << "Failed to start the WebSocketServer on port " << port << Qt::endl;
    }
}

void WebSocketServer::onNewConnection() {
    QWebSocket *socket = qtWS->nextPendingConnection();

    // Setup the signals/slots for the new client
    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessage);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onSocketDisconnected);

    // Add the new client to the list of clients
    clients << socket;

    Console::out << "New connection from " << socket->peerAddress().toString() << Qt::endl;

    // Send the current player state on connection
    socket->sendTextMessage(getStateJson());
}

void WebSocketServer::onTextMessage(QString message) {
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    Console::out << "Request from " << client->peerAddress().toString() << Qt::endl;

    QStringList args = message.split(" ");
    if (args.length() != 0) {
        if (args[0] == "add" && args.length() == 2) { // Add a new track/playlist to the queue
            QJsonDocument json = QJsonDocument::fromJson(ytdl::getJSON(args[1]));

            if (!json.isEmpty() && !json.isArray()) {
                QJsonObject obj = json.object();

                if (obj.contains("_type") && obj["_type"] == "playlist") { // If playlist
                    QJsonArray entries = obj["entries"].toArray();

                    for (int i = 0; i < entries.size(); i++) { // For each media in the playlist
                        QJsonObject entry = entries[i].toObject();

                        Media m = Media::fromJSON(entry);

                        player->addToQueue(m);
                    }
                } else { // If standalone track
                    Media m = Media::fromJSON(obj);
                    player->addToQueue(m);
                }
            }
        } else if (args[0] == "play") { // Resume playback
            player->play();
        } else if (args[0] == "pause") { // Pause playback
            player->pause();
        } else if (args[0] == "next") { // Next media
            player->next();
        } else if (args[0] == "prev") { // Previous media
            player->previous();
        } else if(args[0] == "stop") { // Stop playback
            player->stop();
        } else if(args[0] == "load" && args.length() == 2) { // Load from queue
            player->loadIndex(args[1].toInt());
        } else if(args[0] == "reset") { // Empty the queue
            player->emptyQueue();
        } else if(args[0] == "remove" && args.length() == 2) { // Remove from queue
            int index = args[1].toInt();
            
            if(index < player->getQueue().length()) {
                player->deleteFromQueue(index);
            }
        } else if(args[0] == "position" && args.length() == 2) { // Update the player position
            player->setPosition(args[1].toInt());
        } else if(args[0] == "volume" && args.length() == 2) { // Set the volume
            player->setVolume(args[1].toInt());
        }
    }
}

void WebSocketServer::onSocketDisconnected() {
    QWebSocket *client = qobject_cast<QWebSocket*>(sender());

    if (client) {
        Console::out << "Disconnected from " << client->peerAddress().toString() << Qt::endl;

        clients.removeAll(client); // Remove the client from the list of clients
        client->deleteLater(); // Cleanup memory
    }
}

void WebSocketServer::onPlayerPositionUpdate(qint64 position) {
    QString msg = "pos " + QString::number(position);
    
    for(QWebSocket* client : clients) {
        client->sendTextMessage(msg);
    }
}

QString WebSocketServer::getStateJson() {
    QJsonObject jsonObj;

    // Player state
    switch(player->getQtMediaPlayer()->state()) {
        case QMediaPlayer::State::PlayingState:
            jsonObj.insert("state", QJsonValue::fromVariant("playing"));
            break;
        
        case QMediaPlayer::State::PausedState:
            jsonObj.insert("state", QJsonValue::fromVariant("paused"));
            break;

        case QMediaPlayer::State::StoppedState:
            jsonObj.insert("state", QJsonValue::fromVariant("stopped"));
            break;
    }

    // Index of the currently playing media
    jsonObj.insert("current", player->getCurrentIndex());
    
    // Player queue
    QJsonArray playerQueueJson;
    for(Media m : player->getQueue()) {
        QJsonObject mediaJson;
        
        mediaJson.insert("name",        QJsonValue::fromVariant(m.getName()));
        mediaJson.insert("author",      QJsonValue::fromVariant(m.getAuthor()));
        mediaJson.insert("location",    QJsonValue::fromVariant(m.getLocation()));
        mediaJson.insert("trackID",     QJsonValue::fromVariant(m.getTrackID()));
        mediaJson.insert("duration",    QJsonValue::fromVariant(m.getDuration()));

        playerQueueJson.push_back(mediaJson);
    }

    jsonObj.insert("queue", playerQueueJson);

    jsonObj.insert("volume", player->getVolume());

    // Generate the JSON string
    return QJsonDocument(jsonObj).toJson();
}

void WebSocketServer::updateClients() {
    QString json = getStateJson();

    for(QWebSocket* client : clients) {
        client->sendTextMessage(json);
    }
}