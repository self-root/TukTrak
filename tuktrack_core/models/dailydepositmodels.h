#ifndef DAILYDEPOSITMODELS_H
#define DAILYDEPOSITMODELS_H

#include <QObject>
#include "tuktrack_core_global.h"
#include "dailydepositlistmodel.h"

class TUKTRACK_CORE_EXPORT DailyDepositModels : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DailyDepositListModel *dayShiftModel READ getDayShiftModel CONSTANT FINAL)

    Q_PROPERTY(DailyDepositListModel *nightShiftModel READ getNightShiftModel CONSTANT FINAL)
public:
    explicit DailyDepositModels(QObject *parent = nullptr);

    DailyDepositListModel *getDayShiftModel() const;

    DailyDepositListModel *getNightShiftModel() const;

    Q_INVOKABLE void setCurrentDate(const QDate &date);

private:
    DailyDepositListModel *dayShiftModel = nullptr;
    DailyDepositListModel *nightShiftModel = nullptr;

signals:
};

#endif // DAILYDEPOSITMODELS_H
