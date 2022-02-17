#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QVector>

#include "media.h"

class Player : public QObject {
    Q_OBJECT

    public:
        /**
         * Create a new Player, with an empty queue.
         */
        Player();

        /**
         * Resumes the playback of the currently playing media.
         * Starts it from the start if the current Player was stopped.
         */
        void play();

        /**
         * Pauses the playback of the currently playing media.
         */
        void pause();

        /**
         * Pauses the playback of the current media and restart the playback
         * at the start of the queue if restarted after.
         */
        void stop();

        /**
         * Loads next media.
         */
        void next();

        /**
         * Loads previous media.
         */
        void previous();

        /**
         * Load the media from the queue specified by the index.
         * Does not play it just after.
         * 
         * Args :
         * - unsigned int index : the index in the queue
         * 
         * Return : true if the media has been loaded, false otherwise
         */
        bool loadIndex(unsigned int index);

        /**
         * Sets the player position.
         * 
         * Args :
         * - qint64 position : the position to seek into
         */
        void setPosition(qint64 position);

        /**
         * Add a new media to the queue.
         */
        void addToQueue(Media m);

        /**
         * Delete a media from the queue.
         */
        void deleteFromQueue(int index);

        /**
         * Stops the playback and empty the queue.
         */
        void emptyQueue();

        /**
         * Returns the queue.
         */
        QVector<Media> getQueue();

        /**
         * Returns a pointer to the QMediaPlayer instance.
         */
        QMediaPlayer* getQtMediaPlayer();

        /**
         * Returns the index of the currently playing media in the queue.
         */
        int getCurrentIndex();

        /**
         * Get the current volume.
         */
        int getVolume();

        /**
         * Set the volume. Any value not in the [0; 100] range will be ignored.
         */
        void setVolume(unsigned int value);

    signals:
        /**
         * Emitted when an attribute of the player change.
         */
        void stateUpdated();

    private slots:
        /**
         * Used to detect when to change media.
         */
        void playerStatusChanged(QMediaPlayer::MediaStatus status);

    private:
        QMediaPlayer *qtPlayer;
        QVector<Media> queue;
        int current; // Index in the queue of the currently playing media
};

#endif // PLAYER_H