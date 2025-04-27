#include "tukdriversetting.h"

TukDriverSetting::TukDriverSetting(QObject *parent)
    : QObject{parent}
{}

int TukDriverSetting::id() const
{
    return m_id;
}

void TukDriverSetting::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString TukDriverSetting::tukNumber() const
{
    return m_tukNumber;
}

void TukDriverSetting::setTukNumber(const QString &newTukNumber)
{
    if (m_tukNumber == newTukNumber)
        return;
    m_tukNumber = newTukNumber;
    emit tukNumberChanged();
}

int TukDriverSetting::driverId() const
{
    return m_driverId;
}

void TukDriverSetting::setDriverId(int newDriverId)
{
    if (m_driverId == newDriverId)
        return;
    m_driverId = newDriverId;
    emit driverIdChanged();
}

QString TukDriverSetting::shift() const
{
    return m_shift;
}

void TukDriverSetting::setShift(const QString &newShift)
{
    if (m_shift == newShift)
        return;
    m_shift = newShift;
    emit shiftChanged();
}

QDate TukDriverSetting::startDate() const
{
    return m_startDate;
}

void TukDriverSetting::setStartDate(const QDate &newStartDate)
{
    if (m_startDate == newStartDate)
        return;
    m_startDate = newStartDate;
    emit startDateChanged();
}

QDate TukDriverSetting::endDate() const
{
    return m_endDate;
}

void TukDriverSetting::setEndDate(const QDate &newEndDate)
{
    if (m_endDate == newEndDate)
        return;
    m_endDate = newEndDate;
    emit endDateChanged();
}

int TukDriverSetting::tukId() const
{
    return m_tukId;
}

void TukDriverSetting::setTukId(int newTukId)
{
    if (m_tukId == newTukId)
        return;
    m_tukId = newTukId;
    emit tukIdChanged();
}
