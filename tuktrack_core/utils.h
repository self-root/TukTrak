#ifndef UTILS_H
#define UTILS_H

#include "tuktrack_core_global.h"
#include <QString>

class TUKTRACK_CORE_EXPORT Utils
{
public:
    Utils();
    static QString appDataPath();
    static QString databasePath(const QString &databaseName = "app.db");
};

#endif // UTILS_H
