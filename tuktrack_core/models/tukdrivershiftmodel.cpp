#include "tukdrivershiftmodel.h"
#include "data/databaseaccessmanager.h"

TukDriverShiftModel::TukDriverShiftModel(QObject *parent)
    : QAbstractListModel(parent)
    , drivers(new std::vector<std::unique_ptr<TukDriver>>)
{
}

int TukDriverShiftModel::rowCount(const QModelIndex &parent) const
{
    return drivers->size();
}

QVariant TukDriverShiftModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TukDriver &driver = *drivers->at(index.row());
    switch (role) {
    case NameRole:
        return driver.firstName();
    case ShiftRole:
        return DatabaseAccessManager::instance()->mtukDriverDao.getDriverSetting(driver.id())->shift();
    case ActiveRole:
        return driver.active();
    default:
        break;
    }
    return QVariant();
}

void TukDriverShiftModel::getDrivers(int tukId)
{
    beginResetModel();
    drivers = DatabaseAccessManager::instance()->mtukDriverDao.getDrivers(tukId);
    endResetModel();
}


QHash<int, QByteArray> TukDriverShiftModel::roleNames() const
{
    return QHash<int, QByteArray> {
        {NameRole, "name"},
        {ShiftRole, "shift"},
        {ActiveRole, "isActive"}
    };
}
