#ifndef DASHBOARDMODEL_H
#define DASHBOARDMODEL_H

#include <QObject>
#include "models/tukdetailmodel.h"
#include "tuktrack_core_global.h"
#include "tuktuklistmodel.h"
#include "driverslistmodel.h"
#include "driverdepositmodel.h"
#include "maintenancelistmodel.h"
#include "revenuechartmodel.h"

//TODO Last 5 deposits

class TUKTRACK_CORE_EXPORT DashboardModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int totalActiveTuk READ totalActiveTuk WRITE setTotalActiveTuk NOTIFY totalActiveTukChanged FINAL)
    Q_PROPERTY(int totalActiveDriver READ totalActiveDriver WRITE setTotalActiveDriver NOTIFY totalActiveDriverChanged FINAL)
    Q_PROPERTY(double thisMonthRevenue READ thisMonthRevenue WRITE setThisMonthRevenue NOTIFY thisMonthRevenueChanged FINAL)
    Q_PROPERTY(double thisMonthExpense READ thisMonthExpense WRITE setThisMonthExpense NOTIFY thisMonthExpenseChanged FINAL)
    Q_PROPERTY(MaintenanceListModel *upcomingMaintenanceListModel READ getUpcomingMaintenanceListModel CONSTANT FINAL)
    Q_PROPERTY(RevenueChartModel *revenueChartModel READ getRevenueChartModel CONSTANT FINAL)

public:
    explicit DashboardModel(DriversListModel &driverList, TukTukListModel &tukList, DriverDepositModel &depositList, TukDetailModel &tukDetail, QObject *parent = nullptr);

    int totalActiveTuk() const;
    void setTotalActiveTuk(int newTotalActiveTuk);

    int totalActiveDriver() const;
    void setTotalActiveDriver(int newTotalActiveDriver);
    double thisMonthRevenue() const;
    void setThisMonthRevenue(double newThisMonthRevenue);

    double thisMonthExpense() const;
    void setThisMonthExpense(double newThisMonthExpense);

    MaintenanceListModel *getUpcomingMaintenanceListModel() const;

    RevenueChartModel *getRevenueChartModel() const;

public slots:
    void getTotalRevenue();
    void getTotalExpense();
    void onTukUpdate(int tukId);
    void onTukRemoved(int tukId);
    void onDriverRemoved(int driverId);

private:
    int m_totalActiveTuk = 0;
    int m_totalActiveDriver = 0;
    DriversListModel &driverListModel;
    TukTukListModel &tukListModel;
    DriverDepositModel &driverDepositModel;
    TukDetailModel &tukDetailModel;
    double m_thisMonthRevenue = 0;
    double m_thisMonthExpense = 0;

    MaintenanceListModel *upcomingMaintenanceListModel = nullptr;
    RevenueChartModel *revenueChartModel = nullptr;


signals:
    void totalActiveTukChanged();
    void totalActiveDriverChanged();
    void thisMonthRevenueChanged();
    void thisMonthExpenseChanged();
};

#endif // DASHBOARDMODEL_H
