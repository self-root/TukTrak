#ifndef REVENUECHARTMODEL_H
#define REVENUECHARTMODEL_H

#include <QObject>
#include <QPair>
#include <QMap>

class RevenueChartModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int totalMaintenance READ totalMaintenance WRITE setTotalMaintenance NOTIFY totalMaintenanceChanged FINAL)

    Q_PROPERTY(double totalMaintenanceCost READ totalMaintenanceCost WRITE setTotalMaintenanceCost NOTIFY totalMaintenanceCostChanged FINAL)
public:
    struct Data
    {
        double expense = 0;
        double revenue = 0;
    };
    explicit RevenueChartModel(QObject *parent = nullptr);
    enum Roles{
        MonthRole = Qt::UserRole + 1,
        RevenueRole,
        ExpenseRole,
        ColorRole
    };
    Q_INVOKABLE int rowSize();

    Q_INVOKABLE QVariant dataAt(int index, int role) const;

    Q_INVOKABLE void loadData();

    Q_INVOKABLE void loadData(const QDate &startDate, const QDate &endDate);

    int totalMaintenance() const;
    void setTotalMaintenance(int newTotalMaintenance);

    double totalMaintenanceCost() const;
    void setTotalMaintenanceCost(double newTotalMaintenanceCost);

private:
    QMap<QString, Data> mapData;
    int mTotalMaintenance = 0;
    double mTotalMaintenanceCost = 0;


signals:
    void totalMaintenanceChanged();
    void totalMaintenanceCostChanged();
};

#endif // REVENUECHARTMODEL_H
