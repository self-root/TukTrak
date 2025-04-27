#ifndef TUKTUK_H
#define TUKTUK_H

#include <QObject>
#include <QDate>
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT TukTuk : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString registrationNumber READ registrationNumber WRITE setRegistrationNumber NOTIFY registrationNumberChanged FINAL)

    Q_PROPERTY(QString model READ model WRITE setModel NOTIFY modelChanged FINAL)

    Q_PROPERTY(QDate purchaseDate READ purchaseDate WRITE setPurchaseDate NOTIFY purchaseDateChanged FINAL)

    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged FINAL)

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)

    Q_PROPERTY(int phase READ phase WRITE setPhase NOTIFY phaseChanged FINAL)
public:
    explicit TukTuk(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    QString registrationNumber() const;
    void setRegistrationNumber(const QString &newRegistrationNumber);

    QString model() const;
    void setModel(const QString &newModel);

    QDate purchaseDate() const;
    void setPurchaseDate(const QDate &newPurchaseDate);

    QString status() const;
    void setStatus(const QString &newStatus);

    int phase() const;
    void setPhase(int newPhase);

private:
    int m_id = -1;
    QString m_registrationNumber;
    QString m_model;
    QDate m_purchaseDate;
    int m_phase;
    QString m_status = "active"; // should be "active", "in_maintenance", or "retired"


signals:
    void registrationNumberChanged();
    void modelChanged();
    void purchaseDateChanged();
    void statusChanged();
    void idChanged();
    void phaseChanged();
};

#endif // TUKTUK_H
