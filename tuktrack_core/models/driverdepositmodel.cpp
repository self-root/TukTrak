#include "driverdepositmodel.h"
#include "data/databaseaccessmanager.h"

DriverDepositModel::DriverDepositModel(DepositListType depositListType, QObject *parent)
    : listType(depositListType)
    , QAbstractListModel(parent)
{
    depositList = DriverDepositList(new std::vector<std::unique_ptr<DriverDeposit>>);
}

/*QVariant DriverDepositModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0:
            return QString("Date");
        case 1:
            return QString("Versement (Ar)");
        case 2:
            return QString("Rest (Ar)");
        case 3:
            return QString("Note");
        default:
            break;
        }
    }

    return QVariant();
}
*/
int DriverDepositModel::rowCount(const QModelIndex &parent) const
{
    return depositList->size();
}

QVariant DriverDepositModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    DriverDeposit &deposit = *depositList->at(index.row());
    double expectedAmount = DatabaseAccessManager::instance()->mDepositDao.expectedDepositAmount(deposit.driverId(), deposit.DateOfDeposit().dayOfWeek());
    double amountLeft = expectedAmount - deposit.amount();
    bool hasAmountLeft = amountLeft > 0;
    switch (role) {
        case DateRole:
            return deposit.DateOfDeposit();
        case AmountRole:
            return deposit.amount();
        case RestAmountRole:
        {
            if (amountLeft <= 0)
                return 0;
            return amountLeft;
        }
        case NoteRole:
            return deposit.note();
        case HasDepositLeftRole:
            return hasAmountLeft;
        case DriverName:
            return deposit.getDriverName();
        default:
            break;
    }

    return QVariant();
}

void DriverDepositModel::loadDeposit(int driverId)
{
    beginResetModel();
    depositList = DatabaseAccessManager::instance()->mDepositDao.getDepositList(driverId);
    endResetModel();
}

void DriverDepositModel::loadDeposit()
{
    beginResetModel();
    switch (listType) {
    case DepositListType::ByDriver:
        depositList = DatabaseAccessManager::instance()->mDepositDao.getDepositList(mDriverId);
        break;
    case DepositListType::ByTukTuk:
        depositList = DatabaseAccessManager::instance()->mDepositDao.getDepositList(mTukNumber);
        break;
    default:
        break;
    }

    endResetModel();
}

void DriverDepositModel::addDeposit(int driverId, int tukId, const QVariantMap data)
{
    DriverDeposit deposit;
    deposit.setDriverId(driverId);
    deposit.setTukId(tukId);
    deposit.setAmount(data["amount"].toDouble());
    deposit.setDateOfDeposit(data["date"].toDate());
    deposit.setNote(data["note"].toString());

    DatabaseAccessManager::instance()->mDepositDao.add(deposit);

    loadDeposit();
    emit depositUpdated();
}

void DriverDepositModel::updateDeposit(int index, const QVariantMap data)
{
    int driverId = depositList->at(index)->driverId();
    DriverDeposit deposit;
    deposit.setAmount(data["amount"].toDouble());
    deposit.setNote(data["note"].toString());
    deposit.setDateOfDeposit(data["date"].toDate());
    deposit.setId(depositList->at(index)->id());
    DatabaseAccessManager::instance()->mDepositDao.update(deposit);
    loadDeposit();
    emit depositUpdated();
}

void DriverDepositModel::removeDeposit(int index)
{
    int depositId = depositList->at(index)->id();
    int driverId = depositList->at(index)->driverId();
    DatabaseAccessManager::instance()->mDepositDao.removeDeposit(depositId);
    loadDeposit();
    emit depositUpdated();
}

void DriverDepositModel::setDriverId(int driverId)
{
    mDriverId = driverId;
    listType = DepositListType::ByDriver;
}

void DriverDepositModel::setTukNumber(const QString &tukNumber)
{
    mTukNumber = tukNumber;
    listType = DepositListType::ByTukTuk;
}



QHash<int, QByteArray> DriverDepositModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DateRole] = "depositDate";
    roles[AmountRole] = "amount";
    roles[RestAmountRole] = "rest";
    roles[NoteRole] = "note";
    roles[HasDepositLeftRole] = "hasDepositLeft";
    roles[DriverName] = "driverName";
    roles[DriverId] = "driverId";
    return roles;
}
