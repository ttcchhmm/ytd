#include "ytdl.h"
#include "../console/console.h"

#include <QFile>

QByteArray ytdl::getJSON(QString url) {
    QProcess p;

    p.setProgram(YTDL_EXECUTABLE);

    // See man yt-dlp
    p.setArguments(QStringList() << "--ignore-config" << "--compat-options" << "no-youtube-unavailable-videos" << "-J" << url);
    p.start();
    p.waitForFinished(-1);

    if(p.exitCode() != 0) {
        Console::err << "youtube-dl returned a non zero exit code" << Qt::endl;
    }

    return p.readAllStandardOutput();
}

void ytdl::download(QString url, QString path) {
    if(!QFile(path).exists()) {
        QProcess p;

        p.setStandardOutputFile(YTDL_NORMAL_LOG_FILE);
        p.setStandardErrorFile(YTDL_ERROR_LOG_FILE);
        p.setProgram(YTDL_EXECUTABLE);
        // See man yt-dlp
        p.setArguments(QStringList() << "--ignore-config" << "--compat-options" << "no-youtube-unavailable-videos" << "--no-playlist" << "-f" << "bestaudio[ext=m4a]" << "-o" << path << url);
        
        p.start();
        p.waitForFinished(-1);

        if(p.exitCode() != 0) {
            Console::err << "youtube-dl returned a non zero exit code" << Qt::endl;
        }
    }
}