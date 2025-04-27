#include "driverdepositsetting.h"

const QMap<QString, int> DriverDepositSetting::WEEKDAY_NUMBER = {
    {"Monday", 1},
    {"Tuesday", 2},
    {"Wednesday", 3},
    {"Thursday", 4},
    {"Friday", 5},
    {"Saturday", 6},
    {"Sunday", 7}
};

const QHash<int, QString> DriverDepositSetting::WEEKDAY_NAME = {
    {1, "Monday"},
    {2, "Tuesday"},
    {3, "Wednesday"},
    {4, "Thursday"},
    {5, "Friday"},
    {6, "Saturday"},
    {7, "Sunday"}
};

DriverDepositSetting::DriverDepositSetting(QObject *parent)
    : QObject{parent}
{}

int DriverDepositSetting::id() const
{
    return m_id;
}

void DriverDepositSetting::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

int DriverDepositSetting::driverId() const
{
    return m_driverId;
}

void DriverDepositSetting::setDriverId(int newDriverId)
{
    if (m_driverId == newDriverId)
        return;
    m_driverId = newDriverId;
    emit driverIdChanged();
}

int DriverDepositSetting::dayOfWeek() const
{
    return m_dayOfWeek;
}

void DriverDepositSetting::setDayOfWeek(int newDayOfWeek)
{
    if (m_dayOfWeek == newDayOfWeek)
        return;
    m_dayOfWeek = newDayOfWeek;
    emit dayOfWeekChanged();
}

double DriverDepositSetting::amount() const
{
    return m_amount;
}

void DriverDepositSetting::setAmount(double newAmount)
{
    if (qFuzzyCompare(m_amount, newAmount))
        return;
    m_amount = newAmount;
    emit amountChanged();
}
