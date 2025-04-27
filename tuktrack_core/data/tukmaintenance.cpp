#include "tukmaintenance.h"

TukMaintenance::TukMaintenance(QObject *parent)
    : QObject{parent}
{}

int TukMaintenance::id() const
{
    return m_id;
}

void TukMaintenance::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

int TukMaintenance::tukId() const
{
    return m_tukId;
}

void TukMaintenance::setTukId(int newTukId)
{
    if (m_tukId == newTukId)
        return;
    m_tukId = newTukId;
    emit tukIdChanged();
}

QString TukMaintenance::maintenanceType() const
{
    return m_maintenanceType;
}

void TukMaintenance::setMaintenanceType(const QString &newMaintenanceType)
{
    if (m_maintenanceType == newMaintenanceType)
        return;
    m_maintenanceType = newMaintenanceType;
    emit maintenanceTypeChanged();
}

QString TukMaintenance::description() const
{
    return m_description;
}

void TukMaintenance::setDescription(const QString &newDescription)
{
    if (m_description == newDescription)
        return;
    m_description = newDescription;
    emit descriptionChanged();
}

QDate TukMaintenance::scheduledDate() const
{
    return m_scheduledDate;
}

void TukMaintenance::setScheduledDate(const QDate &newScheduledDate)
{
    if (m_scheduledDate == newScheduledDate)
        return;
    m_scheduledDate = newScheduledDate;
    emit scheduledDateChanged();
}

QDate TukMaintenance::performedDate() const
{
    return m_performedDate;
}

void TukMaintenance::setPerformedDate(const QDate &newPerformedDate)
{
    if (m_performedDate == newPerformedDate)
        return;
    m_performedDate = newPerformedDate;
    emit performedDateChanged();
}

bool TukMaintenance::reccuring() const
{
    return m_reccuring;
}

void TukMaintenance::setReccuring(bool newReccuring)
{
    if (m_reccuring == newReccuring)
        return;
    m_reccuring = newReccuring;
    emit reccuringChanged();
}

int TukMaintenance::reccurenceDays() const
{
    return m_reccurenceDays;
}

void TukMaintenance::setReccurenceDays(int newReccurenceDays)
{
    if (m_reccurenceDays == newReccurenceDays)
        return;
    m_reccurenceDays = newReccurenceDays;
    emit reccurenceDaysChanged();
}

double TukMaintenance::cost() const
{
    return m_cost;
}

void TukMaintenance::setCost(double newCost)
{
    if (qFuzzyCompare(m_cost, newCost))
        return;
    m_cost = newCost;
    emit costChanged();
}

QString TukMaintenance::tukNumber() const
{
    return m_tukNumber;
}

void TukMaintenance::setTukNumber(const QString &newTukNumber)
{
    if (m_tukNumber == newTukNumber)
        return;
    m_tukNumber = newTukNumber;
    emit tukNumberChanged();
}
