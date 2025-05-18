#include "maintenancecostbytypemodel.h"
#include "data/databaseaccessmanager.h"

MaintenanceCostByTypeModel::MaintenanceCostByTypeModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int MaintenanceCostByTypeModel::rowCount(const QModelIndex &parent) const
{
    return maintenanceCost.size();
}

QVariant MaintenanceCostByTypeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

QVariant MaintenanceCostByTypeModel::dataAt(int row, int role) const
{
    if (row >= 0 && row < maintenanceCost.size())
    {
        switch (role) {
        case MaintenanceType:
            return maintenanceCost.at(row).first;
        case CostRole:
            return maintenanceCost.at(row).second;
        default:
            return QVariant();
        }
    }
    return QVariant();
}

void MaintenanceCostByTypeModel::loadData(const QDate &startDate, const QDate &endDate)
{
    beginResetModel();
    maintenanceCost = DatabaseAccessManager::instance()->mMaintenanceDao.maintenanceCostByType(startDate, endDate);
    qDebug() << maintenanceCost;
    endResetModel();
}
