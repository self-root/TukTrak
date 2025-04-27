#ifndef DRIVERDEPOSIT_H
#define DRIVERDEPOSIT_H

#include <QObject>
#include <QDate>
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT DriverDeposit : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)

    Q_PROPERTY(int driverId READ driverId WRITE setDriverId NOTIFY driverIdChanged FINAL)

    Q_PROPERTY(QString driverName READ getDriverName WRITE setDriverName NOTIFY driverNameChanged FINAL)

    Q_PROPERTY(int tukId READ tukId WRITE setTukId NOTIFY tukIdChanged FINAL)

    Q_PROPERTY(QString tukNumber READ tukNumber WRITE setTukNumber NOTIFY tukNumberChanged FINAL)

    Q_PROPERTY(QDate DateOfDeposit READ DateOfDeposit WRITE setDateOfDeposit NOTIFY DateOfDepositChanged FINAL)

    Q_PROPERTY(double amount READ amount WRITE setAmount NOTIFY amountChanged FINAL)

    Q_PROPERTY(QString note READ note WRITE setNote NOTIFY noteChanged FINAL)
public:
    explicit DriverDeposit(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    int driverId() const;
    void setDriverId(int newDriverId);

    QString getDriverName() const;
    void setDriverName(const QString &newDriverName);

    int tukId() const;
    void setTukId(int newTukId);

    QString tukNumber() const;
    void setTukNumber(const QString &newTukNumber);

    QDate DateOfDeposit() const;
    void setDateOfDeposit(const QDate &newDateOfDeposit);

    double amount() const;
    void setAmount(double newAmount);

    QString note() const;
    void setNote(const QString &newNote);

private:
    int m_id = -1;
    int m_driverId = -1;
    QString driverName;
    int m_tukId = -1;
    QString m_tukNumber;
    QDate m_DateOfDeposit;
    double m_amount = 0;
    QString m_note;

signals:
    void idChanged();
    void driverIdChanged();
    void driverNameChanged();
    void tukIdChanged();
    void tukNumberChanged();
    void DateOfDepositChanged();
    void amountChanged();
    void noteChanged();
};

#endif // DRIVERDEPOSIT_H
