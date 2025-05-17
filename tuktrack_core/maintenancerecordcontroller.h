#ifndef MAINTENANCERECORDCONTROLLER_H
#define MAINTENANCERECORDCONTROLLER_H

#include <QObject>
#include <QDate>
#include "tuktrack_core_global.h"
#include "models/detailedmaintenancelistmodel.h"
#include "models/revenuechartmodel.h"
#include "models/maintenancecostbytukmodel.h"

class TUKTRACK_CORE_EXPORT MaintenanceRecordController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate NOTIFY startDateChanged FINAL)

    Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate NOTIFY endDateChanged FINAL)

    Q_PROPERTY(MaintenanceListModel *maintenanceList READ getMaintenanceList CONSTANT FINAL)

    Q_PROPERTY(RevenueChartModel *revenueChartModel READ getRevenueChartModel CONSTANT FINAL)

    Q_PROPERTY(MaintenanceCostByTukModel *maintenanceCostByTuk READ getMaintenanceCostByTuk CONSTANT FINAL)
public:
    explicit MaintenanceRecordController(QObject *parent = nullptr);
    QDate startDate() const;
    void setStartDate(const QDate &newStartDate);

    QDate endDate() const;
    void setEndDate(const QDate &newEndDate);
    MaintenanceListModel *getMaintenanceList() const;

    RevenueChartModel *getRevenueChartModel() const;

    MaintenanceCostByTukModel *getMaintenanceCostByTuk() const;

public slots:
    void dateRangeChanged();

private:
    DetailedMaintenanceListModel *maintenanceList = nullptr;
    QDate mStartDate;
    QDate mEndDate;
    RevenueChartModel *revenueChartModel = nullptr;
    MaintenanceCostByTukModel *maintenanceCostByTuk = nullptr;

signals:
    void startDateChanged();
    void endDateChanged();
};

#endif // MAINTENANCERECORDCONTROLLER_H
