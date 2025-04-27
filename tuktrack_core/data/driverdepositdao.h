#ifndef DRIVERDEPOSITDAO_H
#define DRIVERDEPOSITDAO_H

#include <QObject>
#include "tuktrack_core_global.h"
#include "driverdepositsetting.h"
#include <QSqlDatabase>
#include "driverdeposit.h"

typedef std::unique_ptr<std::vector<std::unique_ptr<DriverDepositSetting>>> DepositSettingList;
typedef std::unique_ptr<std::vector<std::unique_ptr<DriverDeposit>>> DriverDepositList;
class TUKTRACK_CORE_EXPORT DriverDepositDao : public QObject
{
    Q_OBJECT
public:
    explicit DriverDepositDao(QSqlDatabase &database, QObject *parent = nullptr);

    DepositSettingList getDepositSettings(int driverId) const;

    DriverDepositList getDepositList(int driverId) const;

    DriverDepositList getDepositList(const QString &tukNumber);

    void add(DriverDepositSetting &depositSetting) const;

    void add(DriverDeposit &deposit) const;

    void update(const DriverDepositSetting &depositSetting) const;

    void update(const DriverDeposit &deposit) const;

    void removeDeposit(int depositId) const;

    void removeDepositSetting(int depositSettingId) const;

    double expectedDepositAmount(int driverId, int weekDay) const;

    double totalRevenueBetween(const QDate &start, const QDate &end);

    QVector<QPair<QString, double>> monthlyRevenueBetween(const QDate &startDate, const QDate &endDate);
private:
    QSqlDatabase &mDatabase;
signals:
};

#endif // DRIVERDEPOSITDAO_H
