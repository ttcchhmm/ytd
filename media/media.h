#ifndef MEDIA_H
#define MEDIA_H

#include <QString>
#include <QJsonObject>

class Media {
	public:
		/**
		 * Create a new Media instance.
		 * 
		 * Args :
		 * - QString name : The name of the media
		 * - QString location : Where the media can be found (URL ou path to a file)
		 * - QString author : The author of the media (ex: for YouTube videos this will be the uploader)
		 * - QString trackID : A way to identify the media (ex: for YouTube videos this will be the video io)
		 * - int duration : The length of the media, in seconds
		 */
		Media(QString name, QString location, QString author, QString trackID, int duration);

		/**
		 * Returns the name of the media.
		 */
		QString getName();

		/**
		 * Returns the location of the media (URL or file path).
		 */
		QString getLocation();

		/**
		 * Returns the author of the media.
		 */
		QString getAuthor();

		/**
		 * Returns the ID of the track.
		 */
		QString getTrackID();

		/**
		 * Returns the length of the media, in seconds.
		 */
		int getDuration();

		/**
		 * Build a new Media object from youtube-dl JSON data.
		 * 
		 * Args :
		 * - QJsonObject json : youtube-dl json data
		 */
		static Media fromJSON(QJsonObject json);
		
	private:
		QString name;
		QString location;
		QString author;
		QString trackID;
		int duration; // In seconds
};

#endif // MEDIA_H
