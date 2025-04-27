#ifndef TUKDRIVERSETTING_H
#define TUKDRIVERSETTING_H

#include <QObject>
#include <QString>
#include <QDate>

class TukDriverSetting : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)

    Q_PROPERTY(QString tukNumber READ tukNumber WRITE setTukNumber NOTIFY tukNumberChanged FINAL)

    Q_PROPERTY(int driverId READ driverId WRITE setDriverId NOTIFY driverIdChanged FINAL)

    Q_PROPERTY(QString shift READ shift WRITE setShift NOTIFY shiftChanged FINAL)

    Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate NOTIFY startDateChanged FINAL)

    Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate NOTIFY endDateChanged FINAL)

    Q_PROPERTY(int tukId READ tukId WRITE setTukId NOTIFY tukIdChanged FINAL)
public:
    explicit TukDriverSetting(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    QString tukNumber() const;
    void setTukNumber(const QString &newTukNumber);

    int driverId() const;
    void setDriverId(int newDriverId);

    QString shift() const;
    void setShift(const QString &newShift);

    QDate startDate() const;
    void setStartDate(const QDate &newStartDate);

    QDate endDate() const;
    void setEndDate(const QDate &newEndDate);

    int tukId() const;
    void setTukId(int newTukId);

private:
    int m_id = -1;
    QString m_tukNumber;
    int m_driverId = -1;
    QString m_shift;
    QDate m_startDate;
    QDate m_endDate;
    int m_tukId = -1;

signals:
    void idChanged();
    void tukNumberChanged();
    void driverIdChanged();
    void shiftChanged();
    void startDateChanged();
    void endDateChanged();
    void tukIdChanged();
};

#endif // TUKDRIVERSETTING_H
