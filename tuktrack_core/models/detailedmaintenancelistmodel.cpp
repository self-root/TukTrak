#include "detailedmaintenancelistmodel.h"

DetailedMaintenanceListModel::DetailedMaintenanceListModel(QObject *parent)
    : MaintenanceListModel{MaintenanceListModel::DateRange}
{}

int DetailedMaintenanceListModel::totalMaintenance() const
{
    return mTotalMaintenance;
}

void DetailedMaintenanceListModel::setTotalMaintenance(int newTotalMaintenance)
{
    if (mTotalMaintenance == newTotalMaintenance)
        return;
    mTotalMaintenance = newTotalMaintenance;
    emit totalMaintenanceChanged();
}

double DetailedMaintenanceListModel::totalMaintenanceCost() const
{
    return mTotalMaintenanceCost;
}

void DetailedMaintenanceListModel::setTotalMaintenanceCost(double newTotalMaintenanceCost)
{
    if (qFuzzyCompare(mTotalMaintenanceCost, newTotalMaintenanceCost))
        return;
    mTotalMaintenanceCost = newTotalMaintenanceCost;
    emit totalMaintenanceCostChanged();
}

void DetailedMaintenanceListModel::computeDataSummary()
{

}
