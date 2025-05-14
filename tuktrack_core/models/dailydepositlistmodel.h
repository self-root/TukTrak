#ifndef DAILYDEPOSITLISTMODEL_H
#define DAILYDEPOSITLISTMODEL_H

#include <QAbstractListModel>
#include "tuktrack_core_global.h"
#include "driverdepositmodel.h"

class TUKTRACK_CORE_EXPORT DailyDepositListModel : public DriverDepositModel
{
    Q_OBJECT
    Q_PROPERTY(QDate currentDate READ currentDate WRITE setCurrentDate NOTIFY currentDateChanged FINAL)
public:
    explicit DailyDepositListModel(QObject *parent = nullptr);

    QDate currentDate() const;
    void setCurrentDate(const QDate &newCurrentDate);

private:
    QDate mCurrentDate;
    // DriverDepositModel interface

public slots:
    void loadDeposit() override;
signals:
    void currentDateChanged();
};

#endif // DAILYDEPOSITLISTMODEL_H
