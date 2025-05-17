#ifndef DETAILEDMAINTENANCELISTMODEL_H
#define DETAILEDMAINTENANCELISTMODEL_H

#include "maintenancelistmodel.h"
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT DetailedMaintenanceListModel : public MaintenanceListModel
{
    Q_OBJECT
    Q_PROPERTY(int totalMaintenance READ totalMaintenance WRITE setTotalMaintenance NOTIFY totalMaintenanceChanged FINAL)
    Q_PROPERTY(double totalMaintenanceCost READ totalMaintenanceCost WRITE setTotalMaintenanceCost NOTIFY totalMaintenanceCostChanged FINAL)
public:
    explicit DetailedMaintenanceListModel(QObject *parent = nullptr);

    int totalMaintenance() const;
    void setTotalMaintenance(int newTotalMaintenance);

    double totalMaintenanceCost() const;
    void setTotalMaintenanceCost(double newTotalMaintenanceCost);

public slots:
    void computeDataSummary();

signals:
    void totalMaintenanceChanged();

    void totalMaintenanceCostChanged();

private:
    int mTotalMaintenance = 0;
    double mTotalMaintenanceCost = 0;

};

#endif // DETAILEDMAINTENANCELISTMODEL_H
