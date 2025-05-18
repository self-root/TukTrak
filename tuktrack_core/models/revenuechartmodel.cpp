#include "revenuechartmodel.h"
#include <QVariant>
#include "data/databaseaccessmanager.h"

RevenueChartModel::RevenueChartModel(QObject *parent)
    : QObject{parent}
{}

int RevenueChartModel::rowSize()
{
    return mapData.size();
}

QVariant RevenueChartModel::dataAt(int index, int role) const
{
    QString month = mapData.keys().at(index);
    switch (role) {
    case MonthRole:
        return month;
    case RevenueRole:
        return QVariantList{{mapData[month].revenue}};
    case ExpenseRole:
        return QVariantList{{mapData[month].expense}};
    default:
        return QVariant();
    }
}



void RevenueChartModel::loadData()
{
    QDate currentDate = QDate::currentDate();
    QDate endDate = QDate(currentDate.year(), currentDate.month(), currentDate.daysInMonth());
    QDate startDate  = endDate.addMonths(-4);
    QVector<QPair<QString, double>> monthlyRevenue = DatabaseAccessManager::instance()->mDepositDao.monthlyRevenueBetween(startDate, endDate);
    QVector<QPair<QString, double>> monthlyExpenses = DatabaseAccessManager::instance()->mMaintenanceDao.monthlyMaintenanceCostBetween(startDate, endDate);
    for (auto pair : monthlyRevenue)
    {
        if (mapData.contains(pair.first))
            mapData[pair.first].revenue = pair.second;
        else
        {
            Data data;
            data.revenue = pair.second;
            mapData[pair.first] = data;
        }

    }

    for (auto pair : monthlyExpenses)
    {
        if (mapData.contains(pair.first))
            mapData[pair.first].expense = pair.second;
        else
        {
            Data data;
            data.expense = pair.second;
            mapData[pair.first] = data;
        }

    }
}

void RevenueChartModel::loadData(const QDate &startDate, const QDate &endDate)
{
    QVector<QPair<QString, double>> monthlyRevenue = DatabaseAccessManager::instance()->mDepositDao.monthlyRevenueBetween(startDate, endDate);
    QVector<QPair<QString, double>> monthlyExpenses = DatabaseAccessManager::instance()->mMaintenanceDao.monthlyMaintenanceCostBetween(startDate, endDate);
    double tempTotalRevenue = 0;
    double tempTotalExpense = 0;
    mapData.clear();
    for (auto pair : monthlyRevenue)
    {
        tempTotalRevenue += pair.second;
        if (mapData.contains(pair.first))
            mapData[pair.first].revenue = pair.second;
        else
        {
            Data data;
            data.revenue = pair.second;
            mapData[pair.first] = data;
        }

    }

    for (auto pair : monthlyExpenses)
    {
        tempTotalExpense += pair.second;
        if (mapData.contains(pair.first))
            mapData[pair.first].expense = pair.second;
        else
        {
            Data data;
            data.expense = pair.second;
            mapData[pair.first] = data;
        }

    }
    setTotalMaintenance(monthlyExpenses.size());
    setTotalMaintenanceCost(tempTotalExpense);
    setTotalRevenue(tempTotalRevenue);
}

int RevenueChartModel::totalMaintenance() const
{
    return mTotalMaintenance;
}

void RevenueChartModel::setTotalMaintenance(int newTotalMaintenance)
{
    if (mTotalMaintenance == newTotalMaintenance)
        return;
    mTotalMaintenance = newTotalMaintenance;
    emit totalMaintenanceChanged();
}

double RevenueChartModel::totalMaintenanceCost() const
{
    return mTotalMaintenanceCost;
}

void RevenueChartModel::setTotalMaintenanceCost(double newTotalMaintenanceCost)
{
    if (qFuzzyCompare(mTotalMaintenanceCost, newTotalMaintenanceCost))
        return;
    mTotalMaintenanceCost = newTotalMaintenanceCost;
    emit totalMaintenanceCostChanged();
}

double RevenueChartModel::totalRevenue() const
{
    return mTotalRevenue;
}

void RevenueChartModel::setTotalRevenue(double newTotalRevenue)
{
    if (qFuzzyCompare(mTotalRevenue, newTotalRevenue))
        return;
    mTotalRevenue = newTotalRevenue;
    emit totalRevenueChanged();
}

