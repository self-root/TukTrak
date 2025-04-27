#include "utils.h"
#include <QStandardPaths>
#include <QDir>

Utils::Utils() {}

QString Utils::appDataPath()
{
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    if (!dir.exists(appDataLocation))
        dir.mkpath(appDataLocation);
    return appDataLocation;
}

QString Utils::databasePath(const QString &databaseName)
{
    return QDir::cleanPath(appDataPath() + QDir::separator() + databaseName);
}
