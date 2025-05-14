#include "dailydepositmodels.h"

DailyDepositModels::DailyDepositModels(QObject *parent)
    : QObject{parent}
    , dayShiftModel(new DailyDepositListModel(DailyDepositListModel::Day))
    , nightShiftModel(new DailyDepositListModel(DailyDepositListModel::Night))
{}

DailyDepositListModel *DailyDepositModels::getDayShiftModel() const
{
    return dayShiftModel;
}

DailyDepositListModel *DailyDepositModels::getNightShiftModel() const
{
    return nightShiftModel;
}

void DailyDepositModels::setCurrentDate(const QDate &date)
{
    dayShiftModel->setCurrentDate(date);
    nightShiftModel->setCurrentDate(date);
}
