#include "driverslistmodel.h"
#include "data/databaseaccessmanager.h"
#include "data/tukdriversetting.h"

DriversListModel::DriversListModel(QObject *parent)
    : QAbstractListModel(parent)
    , driverList(new std::vector<std::unique_ptr<TukDriver>>)
{
    loadData();
}

int DriversListModel::rowCount(const QModelIndex &parent) const
{
    return driverList->size();
}

QVariant DriversListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const TukDriver &driver = *driverList->at(index.row());
    switch (role) {
    case IdRole:
        return driver.id();
    case FirstnameRole:
        return driver.firstName();
    case LastnameRole:
        return driver.lastName();
    case PhoneRole:
        return driver.phoneNumber();
    case IdNumberRole:
        return driver.idNumber();
    case ActiveRole:
        return driver.active();
    case IdPhotoRole:
        return driver.idPhoto();
    default:
        return QVariant();
    }
}


QHash<int, QByteArray> DriversListModel::roleNames() const
{
    return QHash<int, QByteArray>{
        {IdRole, "id"},
        {FirstnameRole, "firstName"},
        {LastnameRole, "lastName"},
        {PhoneRole, "pnoneNumber"},
        {IdNumberRole, "idNumber"},
        {ActiveRole, "isActive"},
        {IdPhotoRole, "idPhoto"}
    };
}

int DriversListModel::activeDriversCount() const
{
    return m_activeDriversCount;
}

void DriversListModel::setActiveDriversCount(int newActiveDriversCount)
{
    if (m_activeDriversCount == newActiveDriversCount)
        return;
    m_activeDriversCount = newActiveDriversCount;
    emit activeDriversCountChanged();
}

void DriversListModel::countActiveDriver()
{
    int activeDriver = 0;
    for (const std::unique_ptr<TukDriver> &driver: *driverList)
    {
        if (driver->active())
            activeDriver += 1;
    }

    setActiveDriversCount(activeDriver);
}

void DriversListModel::loadData()
{
    beginResetModel();
    driverList = DatabaseAccessManager::instance()->mtukDriverDao.getDrivers();
    std::sort(driverList->begin(), driverList->end(), [](const std::unique_ptr<TukDriver> &a, const std::unique_ptr<TukDriver> &b){
        if (a->active() && b->active())
            return false;
        return a->active();
    });
    endResetModel();
    countActiveDriver();
}

void DriversListModel::loadData(int tukId)
{
    beginResetModel();
    driverList = DatabaseAccessManager::instance()->mtukDriverDao.getDrivers(tukId);
    std::sort(driverList->begin(), driverList->end(), [](const std::unique_ptr<TukDriver> &a, const std::unique_ptr<TukDriver> &b){
        if (a->active() && b->active())
            return false;
        return a->active();
    });
    endResetModel();
}

void DriversListModel::addDriver(const QVariantMap &data)
{
    TukDriver driver;
    driver.setFirstName(data["firstName"].toString());
    driver.setLastName(data["lastName"].toString());
    driver.setIdNumber(data["idNumber"].toString());
    driver.setPhoneNumber(data["phoneNumber"].toString());

    DatabaseAccessManager::instance()->mtukDriverDao.add(driver);
    TukDriverSetting driverSetting;
    driverSetting.setDriverId(driver.id());
    driverSetting.setTukId(DatabaseAccessManager::instance()->mTukTukDao.getId(data["tuktuk"].toString()));
    driverSetting.setShift(data["shift"].toString());
    driverSetting.setStartDate(data["date_start"].toDate());

    DatabaseAccessManager::instance()->mtukDriverDao.add(driverSetting);
    loadData();
}

void DriversListModel::updateDriver(int driverId, int driverSettingId, const QVariantMap &data)
{
    std::unique_ptr<TukDriver> driver =  DatabaseAccessManager::instance()->mtukDriverDao.getDriver(driverId);
    driver->setLastName(data["lastName"].toString());
    driver->setFirstName(data["firstName"].toString());
    driver->setIdNumber(data["idNumber"].toString());
    driver->setPhoneNumber(data["phoneNumber"].toString());
    std::unique_ptr<TukDriverSetting> tukDriverSetting = DatabaseAccessManager::instance()->mtukDriverDao.getDriverSetting(driverId);
    tukDriverSetting->setShift(data["shift"].toString());
    tukDriverSetting->setStartDate(data["date_start"].toDate());
    tukDriverSetting->setTukId(data["tuktukId"].toInt());
    DatabaseAccessManager::instance()->mtukDriverDao.update(*driver.get());
    DatabaseAccessManager::instance()->mtukDriverDao.update(*tukDriverSetting.get());
    loadData();

}

void DriversListModel::retireDriver(int driverId)
{
    DatabaseAccessManager::instance()->mtukDriverDao.retireDriver(driverId);
    loadData();
}

void DriversListModel::activateDriver(int driverId)
{
    DatabaseAccessManager::instance()->mtukDriverDao.activateDriver(driverId);
    loadData();
}

void DriversListModel::removeDriver(int driverId)
{
    DatabaseAccessManager::instance()->mtukDriverDao.removeDriver(driverId);
    loadData();
    emit driverRemoved(driverId);
}
