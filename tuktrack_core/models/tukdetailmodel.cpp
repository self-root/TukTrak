#include "tukdetailmodel.h"
#include "data/databaseaccessmanager.h"


TukDetailModel::TukDetailModel(QObject *parent)
    : QObject{parent}
    , m_tuktuk(new TukTuk)
    , m_tukDriverListModel(new TukDriverShiftModel)
    , m_futureMaintenanceListModel(new MaintenanceListModel(MaintenanceListModel::ListType::FutureMaintenace))
    , m_pastMaintenanceListModel(new MaintenanceListModel(MaintenanceListModel::ListType::PastMaintenance))
    , m_depositListModel(new DriverDepositModel)
    , m_maintenanceTypeListModel(new MaintenanceTypeModel)
{
}

TukTuk *TukDetailModel::tuktuk() const
{
    return m_tuktuk;
}

void TukDetailModel::setTuktuk(TukTuk *newTuktuk)
{
    if (m_tuktuk == newTuktuk)
        return;
    m_tuktuk = newTuktuk;
    emit tuktukChanged();
}

TukDriverShiftModel *TukDetailModel::tukDriverListModel() const
{
    return m_tukDriverListModel;
}

void TukDetailModel::setCurrentTuk(const QString &plateNumber)
{
    setTuktuk(DatabaseAccessManager::instance()->mTukTukDao.get(plateNumber).release());
    m_tukDriverListModel->getDrivers(m_tuktuk->id());
    m_futureMaintenanceListModel->setTukId(m_tuktuk->id());
    m_futureMaintenanceListModel->loadData();
    m_pastMaintenanceListModel->setTukId(m_tuktuk->id());
    m_pastMaintenanceListModel->loadData();
    m_depositListModel->setTukNumber(plateNumber);
    m_depositListModel->loadDeposit();
}

void TukDetailModel::addMaintenance(const QVariantMap &data)
{
    TukMaintenance maintenance;
    maintenance.setTukId(m_tuktuk->id());
    maintenance.setMaintenanceType(data["maintenance_type"].toString());
    maintenance.setDescription(data["description"].toString());
    maintenance.setScheduledDate(data["schedule_date"].toDate());
    maintenance.setCost(data["cost"].toDouble());

    if (data["finished"].toBool())
        maintenance.setPerformedDate(data["performed_date"].toDate());
    else
        maintenance.setPerformedDate(QDate());

    maintenance.setReccuring(data["reccuring"].toBool());
    if (maintenance.reccuring())
        maintenance.setReccurenceDays(data["reccurence"].toInt());
    else
        maintenance.setReccurenceDays(0);

    add(maintenance);

    // Schedule the next maintenance
    if (data["finished"].toBool() && maintenance.reccuring())
    {
        scheduleNextMaintenance(maintenance);
    }

}

void TukDetailModel::add(TukMaintenance &maintenance)
{
    DatabaseAccessManager::instance()->mMaintenanceDao.add(maintenance);
    m_futureMaintenanceListModel->loadData();
    m_pastMaintenanceListModel->loadData();
    m_maintenanceTypeListModel->loadData();

    emit maintenanceUpdated();
}

void TukDetailModel::update(const TukMaintenance &maintenance)
{
    DatabaseAccessManager::instance()->mMaintenanceDao.update(maintenance);
    m_futureMaintenanceListModel->loadData();
    m_pastMaintenanceListModel->loadData();
    emit maintenanceUpdated();
}

void TukDetailModel::scheduleNextMaintenance(TukMaintenance &maintenance)
{
    maintenance.setScheduledDate(maintenance.performedDate().addDays(maintenance.reccurenceDays()));
    maintenance.setPerformedDate(QDate());
    add(maintenance);
}

void TukDetailModel::removeMaintenance(int maintenanceId)
{
    DatabaseAccessManager::instance()->mMaintenanceDao.remove(maintenanceId);
    m_futureMaintenanceListModel->loadData();
    m_pastMaintenanceListModel->loadData();
}

void TukDetailModel::updateMaintenance(int maintenanceId, const QVariantMap &data)
{
    TukMaintenance maintenance;
    maintenance.setTukId(m_tuktuk->id());
    maintenance.setMaintenanceType(data["maintenance_type"].toString());
    maintenance.setDescription(data["description"].toString());
    maintenance.setScheduledDate(data["schedule_date"].toDate());
    maintenance.setCost(data["cost"].toDouble());

    if (data["finished"].toBool())
        maintenance.setPerformedDate(data["performed_date"].toDate());
    else
        maintenance.setPerformedDate(QDate());

    maintenance.setReccuring(data["reccuring"].toBool());
    if (maintenance.reccuring())
        maintenance.setReccurenceDays(data["reccurence"].toInt());
    else
        maintenance.setReccurenceDays(0);
    maintenance.setId(maintenanceId);

    update(maintenance);

    // Schedule the next maintenance
    if (data["finished"].toBool() && maintenance.reccuring())
    {
        scheduleNextMaintenance(maintenance);
    }
}

void TukDetailModel::updateStatus(int tukId, const QString &status)
{
    m_tuktuk->setStatus(status);
    DatabaseAccessManager::instance()->mTukTukDao.changeStatus(tukId, status);
    emit tuktukUpdated(tukId);
}

void TukDetailModel::removeTukTuk(int tukId)
{
    DatabaseAccessManager::instance()->mTukTukDao.remove(tukId);
    setTuktuk(new TukTuk);
    emit tuktukRemoved(tukId);
}

void TukDetailModel::updateCurrentTuk(const QVariantMap &data)
{
    m_tuktuk->setModel(data["model"].toString());
    m_tuktuk->setPhase(data["phase"].toInt());
    m_tuktuk->setPurchaseDate(data["purchaseDate"].toDate());
    m_tuktuk->setRegistrationNumber(data["registrationNumber"].toString());
}

MaintenanceTypeModel *TukDetailModel::maintenanceTypeListModel() const
{
    return m_maintenanceTypeListModel;
}

DriverDepositModel *TukDetailModel::depositListModel() const
{
    return m_depositListModel;
}

MaintenanceListModel *TukDetailModel::pastMaintenanceListModel() const
{
    return m_pastMaintenanceListModel;
}

MaintenanceListModel *TukDetailModel::futureMaintenanceListModel() const
{
    return m_futureMaintenanceListModel;
}
