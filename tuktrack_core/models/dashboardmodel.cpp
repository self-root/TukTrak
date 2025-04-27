#include "dashboardmodel.h"
#include "data/databaseaccessmanager.h"

DashboardModel::DashboardModel(DriversListModel &driverList, TukTukListModel &tukList, DriverDepositModel &depositList, TukDetailModel &tukDetail, QObject *parent)
    : driverListModel(driverList)
    , tukListModel(tukList)
    , driverDepositModel(depositList)
    , tukDetailModel(tukDetail)
    , upcomingMaintenanceListModel(new MaintenanceListModel(MaintenanceListModel::FutureMaintenace))
    , revenueChartModel(new RevenueChartModel)
    , QObject{parent}
{
    getTotalRevenue();
    getTotalExpense();
    setTotalActiveDriver(driverListModel.activeDriversCount());
    setTotalActiveTuk(tukListModel.activeTukCount());
    upcomingMaintenanceListModel->loadData();
    revenueChartModel->loadData();
    QObject::connect(&driverListModel,
                        &DriversListModel::activeDriversCountChanged,
                        this,
                        [&]() {
                            setTotalActiveDriver(driverListModel.activeDriversCount());
                        });

    QObject::connect(&tukListModel,
                    &TukTukListModel::activeTukCountChanged,
                    this,
                    [&](){
                        setTotalActiveTuk(tukListModel.activeTukCount());
                    });
    QObject::connect(&driverDepositModel, &DriverDepositModel::depositUpdated, this, &DashboardModel::getTotalRevenue);
    QObject::connect(&tukDetailModel, &TukDetailModel::maintenanceUpdated, this, &DashboardModel::getTotalExpense);
    QObject::connect(&tukDetailModel, &TukDetailModel::maintenanceUpdated, upcomingMaintenanceListModel, &MaintenanceListModel::loadData);
    QObject::connect(&tukDetailModel, &TukDetailModel::tuktukUpdated, this, &DashboardModel::onTukUpdate);
    QObject::connect(&tukDetailModel, &TukDetailModel::tuktukRemoved, this, &DashboardModel::onTukRemoved);
}

int DashboardModel::totalActiveTuk() const
{
    return m_totalActiveTuk;
}

void DashboardModel::setTotalActiveTuk(int newTotalActiveTuk)
{
    if (m_totalActiveTuk == newTotalActiveTuk)
        return;
    m_totalActiveTuk = newTotalActiveTuk;
    emit totalActiveTukChanged();
}

int DashboardModel::totalActiveDriver() const
{
    return m_totalActiveDriver;
}

void DashboardModel::setTotalActiveDriver(int newTotalActiveDriver)
{
    if (m_totalActiveDriver == newTotalActiveDriver)
        return;
    m_totalActiveDriver = newTotalActiveDriver;
    emit totalActiveDriverChanged();
}

void DashboardModel::getTotalRevenue()
{
    QDate today = QDate::currentDate();
    QDate startDate = QDate(today.year(), today.month(), 1);
    QDate endDate = QDate(today.year(), today.month(), today.daysInMonth());
    setThisMonthRevenue(DatabaseAccessManager::instance()->mDepositDao.totalRevenueBetween(startDate, endDate));
}

void DashboardModel::getTotalExpense()
{
    QDate today = QDate::currentDate();
    QDate startDate = QDate(today.year(), today.month(), 1);
    QDate endDate = QDate(today.year(), today.month(), today.daysInMonth());
    setThisMonthExpense(DatabaseAccessManager::instance()->mMaintenanceDao.maintenanceCostBetween(startDate, endDate));
}

void DashboardModel::onTukUpdate(int tukId)
{
    tukListModel.loadData();
    setTotalActiveTuk(tukListModel.activeTukCount());

}

void DashboardModel::onTukRemoved(int tukId)
{
    tukListModel.loadData();
    setTotalActiveTuk(tukListModel.activeTukCount());
    getTotalRevenue();
    getTotalExpense();
}

void DashboardModel::onDriverRemoved(int driverId)
{
    getTotalRevenue();
}

RevenueChartModel *DashboardModel::getRevenueChartModel() const
{
    return revenueChartModel;
}

MaintenanceListModel *DashboardModel::getUpcomingMaintenanceListModel() const
{
    return upcomingMaintenanceListModel;
}

double DashboardModel::thisMonthExpense() const
{
    return m_thisMonthExpense;
}

void DashboardModel::setThisMonthExpense(double newThisMonthExpense)
{
    if (qFuzzyCompare(m_thisMonthExpense, newThisMonthExpense))
        return;
    m_thisMonthExpense = newThisMonthExpense;
    emit thisMonthExpenseChanged();
}

double DashboardModel::thisMonthRevenue() const
{
    return m_thisMonthRevenue;
}

void DashboardModel::setThisMonthRevenue(double newThisMonthRevenue)
{
    if (qFuzzyCompare(m_thisMonthRevenue, newThisMonthRevenue))
        return;
    m_thisMonthRevenue = newThisMonthRevenue;
    emit thisMonthRevenueChanged();
}
