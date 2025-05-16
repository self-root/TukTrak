#ifndef TUKDRIVERDAO_H
#define TUKDRIVERDAO_H

#include <QObject>
#include "tuktrack_core_global.h"
#include "tukdriver.h"
#include "tukdriversetting.h"


typedef std::unique_ptr<std::vector<std::unique_ptr<TukDriver>>> TukDriverList;

class QSqlDatabase;

class TUKTRACK_CORE_EXPORT TukDriverDao : public QObject
{
    Q_OBJECT
public:
    explicit TukDriverDao(QSqlDatabase &db, QObject *parent = nullptr);

    TukDriverList getDrivers() const;

    TukDriverList getDrivers(int tukId) const;

    TukDriverList getDrivers(const QString &shift) const;

    std::unique_ptr<TukDriver> getDriver(int id) const;

    std::unique_ptr<TukDriverSetting> getDriverSetting(int driverId) const;

    void add(TukDriver &driver) const;

    void add(TukDriverSetting &driverSetting) const;

    void update(const TukDriver &driver) const;
    void update(const TukDriverSetting &driverSetting) const;
    void retireDriver(int driverId) const;
    void activateDriver(int driverId) const;
    void removeDriver(int driverId) const;

private:
    QSqlDatabase &mDatabase;

signals:
};

#endif // TUKDRIVERDAO_H
