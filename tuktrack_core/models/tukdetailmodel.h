#ifndef TUKDETAILMODEL_H
#define TUKDETAILMODEL_H

#include <QObject>
#include "tuktrack_core_global.h"
#include "data/tuktuk.h"
#include "tukdrivershiftmodel.h"
#include "maintenancelistmodel.h"
#include "driverdepositmodel.h"
#include "maintenancetypemodel.h"


class TUKTRACK_CORE_EXPORT TukDetailModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TukTuk *tuktuk READ tuktuk WRITE setTuktuk NOTIFY tuktukChanged FINAL)
    Q_PROPERTY(TukDriverShiftModel *tukDriverListModel READ tukDriverListModel CONSTANT FINAL)
    Q_PROPERTY(MaintenanceListModel *futureMaintenanceListModel READ futureMaintenanceListModel CONSTANT FINAL)
    Q_PROPERTY(MaintenanceListModel *pastMaintenanceListModel READ pastMaintenanceListModel CONSTANT FINAL)
    Q_PROPERTY(DriverDepositModel *depositListModel READ depositListModel CONSTANT FINAL)
    Q_PROPERTY(MaintenanceTypeModel *maintenanceTypeListModel READ maintenanceTypeListModel CONSTANT FINAL)
public:
    explicit TukDetailModel(QObject *parent = nullptr);

    TukTuk *tuktuk() const;
    void setTuktuk(TukTuk *newTuktuk);

    TukDriverShiftModel *tukDriverListModel() const;

    MaintenanceListModel *futureMaintenanceListModel() const;

    MaintenanceListModel *pastMaintenanceListModel() const;

    DriverDepositModel *depositListModel() const;

    MaintenanceTypeModel *maintenanceTypeListModel() const;

public slots:
    void setCurrentTuk(const QString &plateNumber);

    void addMaintenance(const QVariantMap &data);

    void add(TukMaintenance &maintenance);

    void update(const TukMaintenance &maintenance);

    void scheduleNextMaintenance(TukMaintenance &maintenance);

    void removeMaintenance(int maintenanceId);

    void updateMaintenance(int maintenanceId, const QVariantMap &data);

    void updateStatus(int tukId, const QString &status);

    void removeTukTuk(int tukId);

    void updateCurrentTuk(const QVariantMap &data);

private:
    TukTuk *m_tuktuk = nullptr;

    TukDriverShiftModel *m_tukDriverListModel = nullptr;
    MaintenanceListModel *m_futureMaintenanceListModel = nullptr;
    MaintenanceListModel *m_pastMaintenanceListModel = nullptr;
    DriverDepositModel *m_depositListModel = nullptr;
    MaintenanceTypeModel *m_maintenanceTypeListModel = nullptr;


signals:
    void tuktukChanged();
    void maintenanceUpdated();
    void tuktukUpdated(int tukId);
    void tuktukRemoved(int tukId);

};

#endif // TUKDETAILMODEL_H
