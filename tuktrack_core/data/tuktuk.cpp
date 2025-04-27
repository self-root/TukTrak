#include "tuktuk.h"

TukTuk::TukTuk(QObject *parent)
    : QObject{parent}
{}

int TukTuk::id() const
{
    return m_id;
}

void TukTuk::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString TukTuk::registrationNumber() const
{
    return m_registrationNumber;
}

void TukTuk::setRegistrationNumber(const QString &newRegistrationNumber)
{
    if (m_registrationNumber == newRegistrationNumber)
        return;
    m_registrationNumber = newRegistrationNumber;
    emit registrationNumberChanged();
}

QString TukTuk::model() const
{
    return m_model;
}

void TukTuk::setModel(const QString &newModel)
{
    if (m_model == newModel)
        return;
    m_model = newModel;
    emit modelChanged();
}

QDate TukTuk::purchaseDate() const
{
    return m_purchaseDate;
}

void TukTuk::setPurchaseDate(const QDate &newPurchaseDate)
{
    if (m_purchaseDate == newPurchaseDate)
        return;
    m_purchaseDate = newPurchaseDate;
    emit purchaseDateChanged();
}

QString TukTuk::status() const
{
    return m_status;
}

void TukTuk::setStatus(const QString &newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}

int TukTuk::phase() const
{
    return m_phase;
}

void TukTuk::setPhase(int newPhase)
{
    if (m_phase == newPhase)
        return;
    m_phase = newPhase;
    emit phaseChanged();
}
