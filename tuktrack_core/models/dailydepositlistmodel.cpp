#include "dailydepositlistmodel.h"
#include "data/databaseaccessmanager.h"
DailyDepositListModel::DailyDepositListModel(QObject *parent)
    : DriverDepositModel(DepositListType::Daily, parent)
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
    depositList = DatabaseAccessManager::instance()->mDepositDao.getDepositList(mCurrentDate);
    endResetModel();
}
