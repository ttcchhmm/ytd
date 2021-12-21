#include "media.h"

Media::Media(QString name, QString location, QString author, QString trackID, int duration) {
	this->name = name;
	this->location = location;
	this->author = author;
	this->trackID = trackID;
	this->duration = duration;
}

QString Media::getName() {
	return name;
}

QString Media::getLocation() {
	return location;
}

QString Media::getAuthor() {
	return author;
}

QString Media::getTrackID() {
	return trackID;
}

int Media::getDuration() {
	return duration;
}

Media Media::fromJSON(QJsonObject json) {
	return Media(json["title"].toString(),
			json["webpage_url"].toString(),
			json["channel"].toString(),
			json["id"].toString(),
			json["duration"].toInt());
}