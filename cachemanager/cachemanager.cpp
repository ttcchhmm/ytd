#include "cachemanager.h"

QString CacheManager::getCachedPath(Media m) {
    QDir dir(CACHE_DIR);
    dir.mkpath(CACHE_DIR);

    return CACHE_DIR + m.getTrackID() + ".m4a";
}