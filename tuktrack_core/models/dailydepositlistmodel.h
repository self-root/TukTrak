#ifndef DAILYDEPOSITLISTMODEL_H
#define DAILYDEPOSITLISTMODEL_H

#include <QAbstractListModel>
#include "tuktrack_core_global.h"
#include "driverdepositmodel.h"
#include "data/tukdriverdao.h"

class TUKTRACK_CORE_EXPORT DailyDepositListModel : public DriverDepositModel
{
    Q_OBJECT
    Q_PROPERTY(QDate currentDate READ currentDate WRITE setCurrentDate NOTIFY currentDateChanged FINAL)
    Q_PROPERTY(double totalDeposit READ totalDeposit WRITE setTotalDeposit NOTIFY totalDepositChanged FINAL)
public:
    enum Shift{
        Day,
        Night
    };
    explicit DailyDepositListModel(Shift shift, QObject *parent = nullptr);

    QDate currentDate() const;
    void setCurrentDate(const QDate &newCurrentDate);

    double totalDeposit() const;
    void setTotalDeposit(double newTotalDeposit);

    void computeTotalDeposit();

private:
    Shift mShift;
    QDate mCurrentDate;
    // DriverDepositModel interface
    double mTotalDeposit = 0.0;
    TukDriverList drivers;

    void depositFor(int driverId, DriverDeposit *deposit_) const;


public slots:
    void loadDeposit() override;
signals:
    void currentDateChanged();
    void totalDepositChanged();

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
};

#endif // DAILYDEPOSITLISTMODEL_H
