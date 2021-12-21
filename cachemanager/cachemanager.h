#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <QString>
#include <QDir>
#include "../media/media.h"

namespace CacheManager {
    /**
     * Path to the cache directory.
     */
    const QString CACHE_DIR = QDir::toNativeSeparators(QDir::tempPath() + "/ytd/");

    /**
     * Get the path to the cache for the specified media
     * 
     * Args :
     * - Media m : The media to get the path for
     */
    QString getCachedPath(Media m);
}

#endif // CACHEMANAGER_H