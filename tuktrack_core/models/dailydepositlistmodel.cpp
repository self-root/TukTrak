#include "dailydepositlistmodel.h"
#include "data/databaseaccessmanager.h"
DailyDepositListModel::DailyDepositListModel(Shift shift, QObject *parent)
    : mShift(shift)
    , DriverDepositModel(DepositListType::Daily, parent)
{
    QObject::connect(this, &DailyDepositListModel::currentDateChanged, this, &DailyDepositListModel::loadDeposit);
}

QDate DailyDepositListModel::currentDate() const
{
    return mCurrentDate;
}

void DailyDepositListModel::setCurrentDate(const QDate &newCurrentDate)
{
    if (mCurrentDate == newCurrentDate)
        return;
    mCurrentDate = newCurrentDate;
    emit currentDateChanged();
}


void DailyDepositListModel::loadDeposit()
{
    beginResetModel();
    switch (mShift) {
    case Day:
        depositList = DatabaseAccessManager::instance()->mDepositDao.getDepositList(mCurrentDate, "day");
        break;
    case Night:
        depositList = DatabaseAccessManager::instance()->mDepositDao.getDepositList(mCurrentDate, "night");
        break;
    default:
        depositList = DatabaseAccessManager::instance()->mDepositDao.getDepositList(mCurrentDate);
        break;
    }
    endResetModel();
}
