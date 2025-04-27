#include "databaseaccessmanager.h"
#include "../utils.h"
//#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

DatabaseAccessManager *DatabaseAccessManager::_instance = 0;

DatabaseAccessManager::DatabaseAccessManager()
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
    , mTukTukDao(TukTukDao(*mDatabase))
    , mtukDriverDao(TukDriverDao(*mDatabase))
    , mDepositDao(DriverDepositDao(*mDatabase))
    , mMaintenanceDao(MaintenanceDao(*mDatabase))
{
    mDatabase->setDatabaseName(Utils::databasePath(DATABASE));
    if (!mDatabase->open())
        qDebug() << "Unable to open database at: " << Utils::databasePath(DATABASE) << " Err: " << mDatabase->lastError();
    else
    {
        init();
        qDebug() << "Database opened at: " << Utils::databasePath(DATABASE);
    }

}

void DatabaseAccessManager::init()
{
    QSqlQuery query(*mDatabase);

    QStringList queryList = {
        "PRAGMA foreign_keys = ON",
        R"(
        CREATE TABLE IF NOT EXISTS rickshaw (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            registration_number TEXT NOT NULL UNIQUE,
            model TEXT,
            purchase_date TEXT,
            status TEXT CHECK(status IN ('active', 'in_maintenance', 'retired')) DEFAULT 'active',
            phase INTEGER
        )
        )",
        R"(
        CREATE TABLE IF NOT EXISTS driver (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            first_name TEXT,
            last_name TEXT NOT NULL,
            phone TEXT UNIQUE,
            id_number TEXT,
            active INTEGER DEFAULT 1,
            id_photo TEXT
        )
        )",
        R"(
        CREATE TABLE IF NOT EXISTS rickshaw_driver (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            rickshaw_id INTEGER NOT NULL,
            driver_id INTEGER NOT NULL,
            shift TEXT CHECK(shift IN ('day', 'night')) NOT NULL,
            start_date TEXT NOT NULL,
            end_date TEXT,  -- NULL if currently active
            FOREIGN KEY (rickshaw_id) REFERENCES rickshaw(id) ON DELETE CASCADE,
            FOREIGN KEY (driver_id) REFERENCES driver(id) ON DELETE CASCADE
        )
        )",
        R"(
        CREATE TABLE IF NOT EXISTS driver_deposit_setting (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            driver_id INTEGER NOT NULL,
            weekday TEXT CHECK(weekday IN ('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday')) NOT NULL,
            expected_amount INTEGER NOT NULL,
            FOREIGN KEY (driver_id) REFERENCES driver(id) ON DELETE CASCADE
        )
        )",
        R"(
        CREATE TABLE IF NOT EXISTS driver_deposit (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            driver_id INTEGER NOT NULL,
            rickshaw_id INTEGER NOT NULL,
            date TEXT NOT NULL,
            amount_deposited INTEGER NOT NULL,
            note TEXT,
            FOREIGN KEY (driver_id) REFERENCES driver(id) ON DELETE CASCADE,
            FOREIGN KEY (rickshaw_id) REFERENCES rickshaw(id) ON DELETE CASCADE
        )
        )",
        R"(
        CREATE TABLE IF NOT EXISTS maintenance (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            rickshaw_id INTEGER NOT NULL,
            maintenance_type TEXT NOT NULL,
            description TEXT,
            scheduled_date TEXT,
            performed_date TEXT,
            is_recurring INTEGER DEFAULT 0,  -- 1 for true, 0 for false
            recurrence_days INTEGER,
            cost INTEGER DEFAULT 0,
            FOREIGN KEY (rickshaw_id) REFERENCES rickshaw(id) ON DELETE CASCADE
        )
        )",
        R"(
        CREATE TABLE IF NOT EXISTS withdrawal (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date TEXT NOT NULL,
            amount INTEGER NOT NULL,
            reason TEXT,
            note TEXT
        )
        )"
    };

    for (const QString &qStr : queryList) {
        if (!query.exec(qStr)) {
            qDebug() << "Query failed: " << qStr;
            qDebug() << "Error: " << query.lastError().text();
        }
    }
}

DatabaseAccessManager *DatabaseAccessManager::instance()
{
    if (_instance == nullptr)
        _instance = new DatabaseAccessManager();
    return _instance;
}
