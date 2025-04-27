#include "driverdeposit.h"

DriverDeposit::DriverDeposit(QObject *parent)
    : QObject{parent}
{}

int DriverDeposit::id() const
{
    return m_id;
}

void DriverDeposit::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

int DriverDeposit::driverId() const
{
    return m_driverId;
}

void DriverDeposit::setDriverId(int newDriverId)
{
    if (m_driverId == newDriverId)
        return;
    m_driverId = newDriverId;
    emit driverIdChanged();
}

QString DriverDeposit::getDriverName() const
{
    return driverName;
}

void DriverDeposit::setDriverName(const QString &newDriverName)
{
    if (driverName == newDriverName)
        return;
    driverName = newDriverName;
    emit driverNameChanged();
}

int DriverDeposit::tukId() const
{
    return m_tukId;
}

void DriverDeposit::setTukId(int newTukId)
{
    if (m_tukId == newTukId)
        return;
    m_tukId = newTukId;
    emit tukIdChanged();
}

QString DriverDeposit::tukNumber() const
{
    return m_tukNumber;
}

void DriverDeposit::setTukNumber(const QString &newTukNumber)
{
    if (m_tukNumber == newTukNumber)
        return;
    m_tukNumber = newTukNumber;
    emit tukNumberChanged();
}

QDate DriverDeposit::DateOfDeposit() const
{
    return m_DateOfDeposit;
}

void DriverDeposit::setDateOfDeposit(const QDate &newDateOfDeposit)
{
    if (m_DateOfDeposit == newDateOfDeposit)
        return;
    m_DateOfDeposit = newDateOfDeposit;
    emit DateOfDepositChanged();
}

double DriverDeposit::amount() const
{
    return m_amount;
}

void DriverDeposit::setAmount(double newAmount)
{
    if (qFuzzyCompare(m_amount, newAmount))
        return;
    m_amount = newAmount;
    emit amountChanged();
}

QString DriverDeposit::note() const
{
    return m_note;
}

void DriverDeposit::setNote(const QString &newNote)
{
    if (m_note == newNote)
        return;
    m_note = newNote;
    emit noteChanged();
}
