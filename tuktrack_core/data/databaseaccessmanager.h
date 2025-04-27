#ifndef DATABASEACCESSMANAGER_H
#define DATABASEACCESSMANAGER_H

#include <QString>
#include "tuktukdao.h"
#include "tukdriverdao.h"
#include "driverdepositdao.h"
#include "maintenancedao.h"

#include <QSqlDatabase>

class DatabaseAccessManager
{
private:
    DatabaseAccessManager();

    static DatabaseAccessManager *_instance;
    QSqlDatabase *mDatabase = nullptr;
    const QString DATABASE = "tuktuk.db";

    void init();
public:
    static DatabaseAccessManager *instance();
    TukTukDao mTukTukDao;
    TukDriverDao mtukDriverDao;
    DriverDepositDao mDepositDao;
    MaintenanceDao mMaintenanceDao;
};

#endif // DATABASEACCESSMANAGER_H
