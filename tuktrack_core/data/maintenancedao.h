#ifndef MAINTENANCEDAO_H
#define MAINTENANCEDAO_H

#include <QObject>
#include <QSqlDatabase>
#include "tuktrack_core_global.h"
#include "tukmaintenance.h"


typedef TukMaintenance Maintenance;

typedef std::unique_ptr<std::vector<std::unique_ptr<Maintenance>>> MaintenanceList;

class TUKTRACK_CORE_EXPORT MaintenanceDao : public QObject
{
    Q_OBJECT
public:
    explicit MaintenanceDao(QSqlDatabase &database, QObject *parent = nullptr);

    void add(TukMaintenance &maintenance) const;
    void update(const TukMaintenance &maintenance) const;
    std::unique_ptr<TukMaintenance> get(int maintenanceId) const;
    void remove(int maintenanceId) const;
    MaintenanceList getScheduledMaintenances() const;
    MaintenanceList getScheduledMaintenances(int tukId) const;
    MaintenanceList getPastMaintenances() const;
    MaintenanceList getPastMaintenances(int tukId) const;
    MaintenanceList getPastMaintenances(const QDate &startDate, const QDate &endDate) const;
    double maintenanceCostBetween(const QDate &startDate, const QDate &endDate);
    QVector<QPair<QString, double>> monthlyMaintenanceCostBetween(const QDate &startDate, const QDate &endDate);
    QVector<QPair<QString, int>> getMaintenanceTypes();
    QVector<QPair<QString, double>> maintenanceCostByTukTuk(const QDate &startDate, const QDate &endDate);
    QVector<QPair<QString, double>> maintenanceCostByType(const QDate &startDate, const QDate &endDate);
private:
    QSqlDatabase &mDatabase;
signals:
};

#endif // MAINTENANCEDAO_H
