#ifndef TUKMAINTENANCE_H
#define TUKMAINTENANCE_H

#include <QObject>
#include <QDate>
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT TukMaintenance : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)

    Q_PROPERTY(int tukId READ tukId WRITE setTukId NOTIFY tukIdChanged FINAL)

    Q_PROPERTY(QString maintenanceType READ maintenanceType WRITE setMaintenanceType NOTIFY maintenanceTypeChanged FINAL)

    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged FINAL)

    Q_PROPERTY(QDate scheduledDate READ scheduledDate WRITE setScheduledDate NOTIFY scheduledDateChanged FINAL)

    Q_PROPERTY(QDate performedDate READ performedDate WRITE setPerformedDate NOTIFY performedDateChanged FINAL)

    Q_PROPERTY(bool reccuring READ reccuring WRITE setReccuring NOTIFY reccuringChanged FINAL)

    Q_PROPERTY(int reccurenceDays READ reccurenceDays WRITE setReccurenceDays NOTIFY reccurenceDaysChanged FINAL)

    Q_PROPERTY(double cost READ cost WRITE setCost NOTIFY costChanged FINAL)

    Q_PROPERTY(QString tukNumber READ tukNumber WRITE setTukNumber NOTIFY tukNumberChanged FINAL)
public:
    explicit TukMaintenance(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    int tukId() const;
    void setTukId(int newTukId);

    QString maintenanceType() const;
    void setMaintenanceType(const QString &newMaintenanceType);

    QString description() const;
    void setDescription(const QString &newDescription);

    QDate scheduledDate() const;
    void setScheduledDate(const QDate &newScheduledDate);

    QDate performedDate() const;
    void setPerformedDate(const QDate &newPerformedDate);

    bool reccuring() const;
    void setReccuring(bool newReccuring);

    int reccurenceDays() const;
    void setReccurenceDays(int newReccurenceDays);

    double cost() const;
    void setCost(double newCost);

    QString tukNumber() const;
    void setTukNumber(const QString &newTukNumber);

private:
    int m_id = -1;
    int m_tukId = -1;
    QString m_tukNumber;
    QString m_maintenanceType;
    QString m_description;
    QDate m_scheduledDate;
    QDate m_performedDate;
    bool m_reccuring = false;
    int m_reccurenceDays = 0;
    double m_cost = 0.0;

signals:
    void idChanged();
    void tukIdChanged();
    void maintenanceTypeChanged();
    void descriptionChanged();
    void scheduledDateChanged();
    void performedDateChanged();
    void reccuringChanged();
    void reccurenceDaysChanged();
    void costChanged();
    void tukNumberChanged();
};

#endif // TUKMAINTENANCE_H
