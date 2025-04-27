#ifndef DRIVERDEPOSITSETTING_H
#define DRIVERDEPOSITSETTING_H

#include <QObject>
#include <QMap>
#include <QHash>
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT DriverDepositSetting : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)

    Q_PROPERTY(int driverId READ driverId WRITE setDriverId NOTIFY driverIdChanged FINAL)

    Q_PROPERTY(int dayOfWeek READ dayOfWeek WRITE setDayOfWeek NOTIFY dayOfWeekChanged FINAL)

    Q_PROPERTY(double amount READ amount WRITE setAmount NOTIFY amountChanged FINAL)
public:
    static const QMap<QString, int> WEEKDAY_NUMBER;

    static const QHash<int, QString> WEEKDAY_NAME;

    explicit DriverDepositSetting(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    int driverId() const;
    void setDriverId(int newDriverId);

    int dayOfWeek() const;
    void setDayOfWeek(int newDayOfWeek);

    double amount() const;
    void setAmount(double newAmount);

private:
    int m_id = -1;
    int m_driverId = -1;
    int m_dayOfWeek = 1;
    double m_amount = 0.0;

signals:
    void idChanged();
    void driverIdChanged();
    void dayOfWeekChanged();
    void amountChanged();
};

#endif // DRIVERDEPOSITSETTING_H
