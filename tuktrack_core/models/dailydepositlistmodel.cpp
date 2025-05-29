#include "dailydepositlistmodel.h"
#include "data/databaseaccessmanager.h"
DailyDepositListModel::DailyDepositListModel(Shift shift, QObject *parent)
    : mShift(shift)
    , DriverDepositModel(DepositListType::Daily, parent)
    , drivers(new std::vector<std::unique_ptr<TukDriver>>)
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

double DailyDepositListModel::totalDeposit() const
{
    return mTotalDeposit;
}

void DailyDepositListModel::setTotalDeposit(double newTotalDeposit)
{
    if (qFuzzyCompare(mTotalDeposit, newTotalDeposit))
        return;
    mTotalDeposit = newTotalDeposit;
    emit totalDepositChanged();
}

void DailyDepositListModel::computeTotalDeposit()
{
    double total = 0;
    for (const std::unique_ptr<DriverDeposit> &deposit: *depositList)
    {
        total += deposit->amount();
    }

    setTotalDeposit(total);
}

void DailyDepositListModel::depositFor(int driverId, DriverDeposit *deposit_) const
{
    for (const  std::unique_ptr<DriverDeposit> &deposit: *depositList)
    {
        if (deposit->driverId() == driverId)
            deposit_ = deposit.get();
    }
}


void DailyDepositListModel::loadDeposit()
{
    beginResetModel();
    switch (mShift) {
    case Day:{
        depositList = DatabaseAccessManager::instance()->mDepositDao.getDepositList(mCurrentDate, "day");
        drivers = DatabaseAccessManager::instance()->mtukDriverDao.getDrivers("day");
        break;
    }
    case Night: {
        depositList = DatabaseAccessManager::instance()->mDepositDao.getDepositList(mCurrentDate, "night");
        drivers = DatabaseAccessManager::instance()->mtukDriverDao.getDrivers("night");
        break;
    }
    default:
        depositList = DatabaseAccessManager::instance()->mDepositDao.getDepositList(mCurrentDate);
        break;
    }
    endResetModel();
    computeTotalDeposit();
}


QVariant DailyDepositListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TukDriver &driver = *drivers->at(index.row());
    std::unique_ptr<DriverDeposit> deposit = DatabaseAccessManager::instance()->mDepositDao.getDeposit(driver.id(), mCurrentDate);
    double expectedAmount = DatabaseAccessManager::instance()->mDepositDao.expectedDepositAmount(deposit->driverId(), deposit->DateOfDeposit().dayOfWeek());
    double amountLeft = expectedAmount - deposit->amount();
    bool hasAmountLeft = amountLeft > 0;
    switch (role) {
    case DateRole:
        return deposit->DateOfDeposit();
    case AmountRole:
        return deposit->amount();
    case RestAmountRole:
    {
        if (amountLeft <= 0)
            return 0;
        return amountLeft;
    }
    case NoteRole:
        return deposit->note();
    case HasDepositLeftRole:
        return hasAmountLeft;
    case DriverName:
        return driver.lastName() + " " + driver.firstName();
    case DriverId:
        return driver.id();
    default:
        break;
    }

    return QVariant();
}


int DailyDepositListModel::rowCount(const QModelIndex &parent) const
{
    return drivers->size();
}
