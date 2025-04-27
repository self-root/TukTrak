#include "maintenancetypemodel.h"
#include "data/databaseaccessmanager.h"

MaintenanceTypeModel::MaintenanceTypeModel(QObject *parent)
    : QAbstractListModel(parent)
{
    loadData();
}

int MaintenanceTypeModel::rowCount(const QModelIndex &parent) const
{
    return maintenanceTypesList.size();
}

QVariant MaintenanceTypeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QPair<QString, int> maintenanceType = maintenanceTypesList.at(index.row());
    switch (role) {
    case MaintenanaceTypeRole:
        return maintenanceType.first;
    case MaintenanceCountRole:
        return maintenanceType.second;
    default:
        break;
    }
    return QVariant();
}

void MaintenanceTypeModel::loadData()
{
    beginResetModel();
    maintenanceTypesList = DatabaseAccessManager::instance()->mMaintenanceDao.getMaintenanceTypes();
    endResetModel();
}


QHash<int, QByteArray> MaintenanceTypeModel::roleNames() const
{
    return {
        {MaintenanaceTypeRole, "maintenanceType"},
        {MaintenanceCountRole, "maintenanceCount"}
    };
}
