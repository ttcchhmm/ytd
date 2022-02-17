#include "player.h"

#include <QUrl>

#include "../cachemanager/cachemanager.h"
#include "../yt-dl/ytdl.h"

Player::Player() {
    qtPlayer = new QMediaPlayer(this);

    current = -1;
    QObject::connect(qtPlayer, &QMediaPlayer::mediaStatusChanged, this, &Player::playerStatusChanged);
}

void Player::play() {
    if(qtPlayer->state() != QMediaPlayer::State::StoppedState || current != -1) {
        qtPlayer->play();

        emit stateUpdated();
    } else {
        next();
    }
}

void Player::pause() {
    qtPlayer->pause();

    emit stateUpdated();
}

void Player::stop() {
    qtPlayer->stop();
    current = -1;

    emit stateUpdated();
}

void Player::setPosition(qint64 position) {
    qtPlayer->setPosition(position);
    // No need to emit stateUpdated because the position signal of the QMediaPlayer is already monitored by the server
}

void Player::addToQueue(Media m) {
    queue.append(m);

    emit stateUpdated();
}

void Player::deleteFromQueue(int index) {  
    queue.remove(index);

    if(current == index) {
        next();
    } else if (current >= queue.length()) {
        stop();
        return; // Avoid sending two updates in a row
    }

    emit stateUpdated();
}

void Player::emptyQueue() {
    stop();
    queue = QVector<Media>();

    emit stateUpdated();
}

QVector<Media> Player::getQueue() {
    return queue;
}

QMediaPlayer* Player::getQtMediaPlayer() {
    return qtPlayer;
}

int Player::getCurrentIndex() {
    return current;
}

void Player::next() {
    if(loadIndex(current+1)) {
        play();
    } else {
        emit stateUpdated(); // Used to send the end of the queue
    }
}

void Player::previous() {
    if(loadIndex(current-1)) {
        play();
    } else {
        emit stateUpdated();
    }
}

int Player::getVolume() {
    return qtPlayer->volume();
}

void Player::setVolume(unsigned int value) {
    if(value <= 100) {
        qtPlayer->setVolume(value);

        emit stateUpdated();
    }
}

bool Player::loadIndex(unsigned int index) {
    if(index < queue.length()) {
        Media m = queue[index];
        QString dlPath = CacheManager::getCachedPath(m);
        ytdl::download(m.getLocation(), dlPath);

        qtPlayer->setMedia(QUrl::fromLocalFile(dlPath));
        current = index;

        emit stateUpdated();

        return true;
    }

    return false;
}

void Player::playerStatusChanged(QMediaPlayer::MediaStatus status) {
    if(status == QMediaPlayer::MediaStatus::EndOfMedia) { // If the current media is finished, load the next one.
        next();
    }
}