#include "maintenancecostbytukmodel.h"
#include "data/databaseaccessmanager.h"

MaintenanceCostByTukModel::MaintenanceCostByTukModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int MaintenanceCostByTukModel::rowCount(const QModelIndex &parent) const
{
    return maintenanceCostByTuc.size();
}

QVariant MaintenanceCostByTukModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

QVariant MaintenanceCostByTukModel::dataAt(int row, int role)
{
    if (row >= 0 && row < maintenanceCostByTuc.size())
    {
        switch (role) {
        case TukNumberRole:
            return maintenanceCostByTuc.at(row).first;
        case CostRole:
            return maintenanceCostByTuc.at(row).second;
        default:
            return QVariant();
        }
    }
    return QVariant();
}

void MaintenanceCostByTukModel::loadData(const QDate &startDate, const QDate &endDate)
{
    beginResetModel();
    maintenanceCostByTuc = DatabaseAccessManager::instance()->mMaintenanceDao.maintenanceCostByTukTuk(startDate, endDate);
    endResetModel();
}
