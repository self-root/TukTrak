#include "driverdetailmodel.h"
#include "data/databaseaccessmanager.h"
#include "androidapi.h"

DriverDetailModel::DriverDetailModel(QObject *parent)
    : QObject{parent}
    , m_driver(new TukDriver)
    , m_driverSetting(new TukDriverSetting)
{}

void DriverDetailModel::setCurrentDriverId(int id)
{
    setDriver(DatabaseAccessManager::instance()->mtukDriverDao.getDriver(id).release());
    setDriverSetting(DatabaseAccessManager::instance()->mtukDriverDao.getDriverSetting(id).release());
}

void DriverDetailModel::callDriver()
{
    AndroidApi::dialNumber(m_driver->phoneNumber());
}

TukDriverSetting *DriverDetailModel::driverSetting() const
{
    return m_driverSetting;
}

void DriverDetailModel::setDriverSetting(TukDriverSetting *newDriverSetting)
{
    if (m_driverSetting == newDriverSetting)
        return;
    m_driverSetting = newDriverSetting;
    emit driverSettingChanged();
}

TukDriver *DriverDetailModel::driver() const
{
    return m_driver;
}

void DriverDetailModel::setDriver(TukDriver *newDriver)
{
    if (m_driver->equal(*newDriver))
        return;
    m_driver = newDriver;
    emit driverChanged();
}

void DriverDetailModel::resetDriver()
{
    //setDriver(new TukDriver);
}
