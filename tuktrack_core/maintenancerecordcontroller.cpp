#include "maintenancerecordcontroller.h"

MaintenanceRecordController::MaintenanceRecordController(QObject *parent)
    : QObject{parent}
    , maintenanceList( new DetailedMaintenanceListModel())
    , revenueChartModel(new RevenueChartModel)
    , maintenanceCostByTuk(new MaintenanceCostByTukModel)
{
    QObject::connect(this, &MaintenanceRecordController::startDateChanged, this, [&](){
        maintenanceList->startDate = mStartDate;
        dateRangeChanged();
    });

    QObject::connect(this, &MaintenanceRecordController::endDateChanged, this, [&](){
        maintenanceList->endDate = mEndDate;
        dateRangeChanged();
    });

    setEndDate(QDate::currentDate());
    setStartDate(mEndDate.addMonths(-4));

}

QDate MaintenanceRecordController::startDate() const
{
    return mStartDate;
}

void MaintenanceRecordController::setStartDate(const QDate &newStartDate)
{
    if (mStartDate == newStartDate)
        return;
    mStartDate = newStartDate;
    emit startDateChanged();
}

QDate MaintenanceRecordController::endDate() const
{
    return mEndDate;
}

void MaintenanceRecordController::setEndDate(const QDate &newEndDate)
{
    if (mEndDate == newEndDate)
        return;
    mEndDate = newEndDate;
    emit endDateChanged();
}

void MaintenanceRecordController::dateRangeChanged()
{
    maintenanceList->loadData();
    maintenanceCostByTuk->loadData(mStartDate, mEndDate);
}

MaintenanceCostByTukModel *MaintenanceRecordController::getMaintenanceCostByTuk() const
{
    return maintenanceCostByTuk;
}

RevenueChartModel *MaintenanceRecordController::getRevenueChartModel() const
{
    return revenueChartModel;
}

MaintenanceListModel *MaintenanceRecordController::getMaintenanceList() const
{
    return maintenanceList;
}
