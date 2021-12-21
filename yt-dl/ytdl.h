#ifndef YTDL_H
#define YTDL_H

#include <QString>
#include <QProcess>
#include <QByteArray>
#include <QDir>

namespace ytdl {
    /**
     * The executable of youtube-dl (or a drop-in replacement). Hardcoded for now
     */
    const QString YTDL_EXECUTABLE = "yt-dlp"; // TODO don't hardcode
    
    /**
     * The location of youtube-dl standard output when not in JSON mode.
     */
    const QString YTDL_NORMAL_LOG_FILE = QDir::toNativeSeparators(QDir::tempPath() + "/ytd/youtube-dl.log");

    /**
     * The location of youtube-dl error output when not in JSON mode.
     */
    const QString YTDL_ERROR_LOG_FILE = QDir::toNativeSeparators(QDir::tempPath() + "/ytd/youtube-dl.err");;
    
    /**
     * Run a youtube-dl request in JSON mode. Not used for downloading.
     * 
     * Args :
     * - QString url : The URL to request data for
     */
    QByteArray getJSON(QString url);

    /**
     * Download content.
     * 
     * Args :
     * - QString url : The URL where the content is located
     * - QString path : The path to download to
     */
    void download(QString url, QString path);
}

#endif // YTDL_H