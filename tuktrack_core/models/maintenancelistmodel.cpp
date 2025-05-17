#include "maintenancelistmodel.h"
#include "data/databaseaccessmanager.h"

MaintenanceListModel::MaintenanceListModel(ListType listType, QObject *parent)
    : mListType(listType)
    , QAbstractListModel(parent)
    , maintenanceList(new std::vector<std::unique_ptr<TukMaintenance>>)
{}

int MaintenanceListModel::rowCount(const QModelIndex &parent) const
{
    return maintenanceList->size();
}

QVariant MaintenanceListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TukMaintenance &maintenance = *maintenanceList->at(index.row());
    switch (role) {
    case IdRole:
        return maintenance.id();
    case TukIdRole:
        return maintenance.tukId();
    case TukNumberRole:
        return maintenance.tukNumber();
    case MaintenanceTypeRole:
        return maintenance.maintenanceType();
    case DescriptionRole:
        return maintenance.description();
    case ScheduleDateRole:
        return maintenance.scheduledDate();
    case PerformedDateRole:
        return maintenance.performedDate();
    case ReccuringRole:
        return maintenance.reccuring();
    case ReccurenceRole:
        return maintenance.reccurenceDays();
    case CostRole:
        return maintenance.cost();
    default:
        break;
    }

    return QVariant();
}

void MaintenanceListModel::loadData()
{
    beginResetModel();
    switch (mListType) {
    case FutureMaintenace:{
        if (mTukId > 0)
            maintenanceList = DatabaseAccessManager::instance()->mMaintenanceDao.getScheduledMaintenances(mTukId);
        else
            maintenanceList = DatabaseAccessManager::instance()->mMaintenanceDao.getScheduledMaintenances();
        break;
    }
    case PastMaintenance: {
        if (mTukId > 0)
            maintenanceList = DatabaseAccessManager::instance()->mMaintenanceDao.getPastMaintenances(mTukId);
        else
            maintenanceList = DatabaseAccessManager::instance()->mMaintenanceDao.getPastMaintenances();
        break;
    }
    case DateRange: {
        maintenanceList = DatabaseAccessManager::instance()->mMaintenanceDao.getPastMaintenances(startDate, endDate);
        break;
    }
    default:
        break;
    }
    endResetModel();
}

void MaintenanceListModel::setTukId(int newTukId)
{
    mTukId = newTukId;
}


QHash<int, QByteArray> MaintenanceListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[IdRole] = "maintenanceId";
    roles[TukIdRole] = "tukId";
    roles[TukNumberRole] = "tukNumber";
    roles[MaintenanceTypeRole] = "maintenanceType";
    roles[DescriptionRole] = "description";
    roles[ScheduleDateRole] = "schduleDate";
    roles[PerformedDateRole] = "performedDate";
    roles[ReccuringRole] = "reccuring";
    roles[ReccurenceRole] = "reccurenceDay";
    roles[CostRole] = "cost";

    return roles;
}
