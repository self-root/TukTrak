#include "tukdriverdao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

TukDriverDao::TukDriverDao(QSqlDatabase &db, QObject *parent)
    : mDatabase(db)
    , QObject{parent}
{}

TukDriverList TukDriverDao::getDrivers() const
{
    TukDriverList list(new std::vector<std::unique_ptr<TukDriver>>);

    QSqlQuery query(mDatabase);

    if (!query.exec("SELECT * FROM driver ORDER BY id DESC"))
    {
        qDebug() << "Unable to get drivers from db: " << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        std::unique_ptr<TukDriver> driver(new TukDriver);
        driver->setId(query.value("id").toInt());
        driver->setFirstName(query.value("first_name").toString());
        driver->setLastName(query.value("last_name").toString());
        driver->setPhoneNumber(query.value("phone").toString());
        driver->setIdNumber(query.value("id_number").toString());
        driver->setActive(query.value("active").toBool());
        driver->setIdPhoto(query.value("id_photo").toString());

        list->push_back(std::move(driver));
    }

    return list;
}

TukDriverList TukDriverDao::getDrivers(int tukId) const
{
    TukDriverList list(new std::vector<std::unique_ptr<TukDriver>>);

    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM driver
        INNER JOIN rickshaw_driver ON rickshaw_driver.driver_id = driver.id
        WHERE rickshaw_driver.rickshaw_id = :tukId
        ORDER BY id DESC
    )");

    query.bindValue(":tukId", tukId);

    if (!query.exec())
    {
        qDebug() << "Unable to get drivers from db: " << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        std::unique_ptr<TukDriver> driver(new TukDriver);
        driver->setId(query.value("id").toInt());
        driver->setFirstName(query.value("first_name").toString());
        driver->setLastName(query.value("last_name").toString());
        driver->setPhoneNumber(query.value("phone").toString());
        driver->setIdNumber(query.value("id_number").toString());
        driver->setActive(query.value("active").toBool());
        driver->setIdPhoto(query.value("id_photo").toString());
        qDebug() << driver->firstName();

        list->push_back(std::move(driver));
    }

    return list;
}

std::unique_ptr<TukDriver> TukDriverDao::getDriver(int id) const
{
    std::unique_ptr<TukDriver> driver(new TukDriver);

    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM driver WHERE id = :id");
    query.bindValue(":id", id);

    if(!query.exec())
    {
        qDebug() << "Unable to get driver: " << id << " from db: " << query.lastError().text();
        return std::move(driver);
    }

    if (query.next())
    {
        driver->setId(id);
        driver->setFirstName(query.value("first_name").toString());
        driver->setLastName(query.value("last_name").toString());
        driver->setPhoneNumber(query.value("phone").toString());
        driver->setIdNumber(query.value("id_number").toString());
        driver->setActive(query.value("active").toBool());
        driver->setIdPhoto(query.value("id_photo").toString());
    }

    return std::move(driver);
}

std::unique_ptr<TukDriverSetting> TukDriverDao::getDriverSetting(int driverId) const
{
    std::unique_ptr<TukDriverSetting> driverSetting(new TukDriverSetting);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM rickshaw_driver
        INNER JOIN rickshaw ON rickshaw.id = rickshaw_id
        WHERE driver_id = :id)");

    query.bindValue(":id", driverId);

    if(!query.exec())
    {
        qDebug() << "Unable to get driver setting: " << driverId << " from db: " << query.lastError().text();
        return std::move(driverSetting);
    }

    if (query.next())
    {
        driverSetting->setId(query.value("rickshaw_driver.id").toInt());
        driverSetting->setTukNumber(query.value("registration_number").toString());
        driverSetting->setDriverId(driverId);
        driverSetting->setShift(query.value("shift").toString());
        driverSetting->setStartDate(QDate::fromString(query.value("start_date").toString(), Qt::ISODate));
        driverSetting->setTukId(query.value("rickshaw_id").toInt());
    }

    return std::move(driverSetting);
}

void TukDriverDao::add(TukDriver &driver) const
{
    QSqlQuery query(mDatabase);

    query.prepare(R"(
        INSERT INTO driver(first_name, last_name, phone, id_number, id_photo)
        VALUES (:first_name, :last_name, :phone, :id_number, :id_photo)
    )");

    query.bindValue(":first_name", driver.firstName());
    query.bindValue(":last_name", driver.lastName());
    query.bindValue(":phone", driver.phoneNumber());
    query.bindValue(":id_number", driver.idNumber());
    query.bindValue(":id_photo", driver.idPhoto());

    if (!query.exec())
    {
        qDebug() << "Insertion error: " << query.lastError().text();
        return;
    }

    driver.setId(query.lastInsertId().toInt());

}

void TukDriverDao::add(TukDriverSetting &driverSetting) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO rickshaw_driver(rickshaw_id, driver_id, shift, start_date)
        VALUES (:rickshaw_id, :driver_id, :shift, :start_date)
    )");

    query.bindValue(":rickshaw_id", driverSetting.tukId());
    query.bindValue(":driver_id", driverSetting.driverId());
    query.bindValue(":shift", driverSetting.shift());
    query.bindValue(":start_date", driverSetting.startDate().toString(Qt::ISODate));

    if (!query.exec())
    {
        qDebug() << "Could not add rickshaw driver setting to the db: " << query.lastError().text();
        return;
    }

    driverSetting.setId(query.lastInsertId().toInt());
}

void TukDriverDao::update(const TukDriver &driver) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE driver
        SET last_name = :lastName,
            first_name = :firstName,
            phone = :phone,
            id_number = :idNumber
        WHERE id = :id
    )");
    query.bindValue(":lastName", driver.lastName());
    query.bindValue(":firstName", driver.firstName());
    query.bindValue(":phone", driver.phoneNumber());
    query.bindValue(":idNumber", driver.idNumber());
    query.bindValue(":id", driver.id());

    if (!query.exec())
        qDebug() << "Unable to update driver: " << query.boundValues() << query.lastError().text();
}

void TukDriverDao::update(const TukDriverSetting &driverSetting) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE rickshaw_driver
        SET rickshaw_id = :rickshaw_id,
            shift = :shift,
            start_date = :start_date
        WHERE id = :id
    )");

    query.bindValue(":rickshaw_id", driverSetting.tukId());
    query.bindValue(":shift", driverSetting.shift());
    query.bindValue(":start_date", driverSetting.startDate());
    query.bindValue(":id", driverSetting.id());
    if (!query.exec())
        qDebug() << "Unable to update driver setting: " << query.lastError().text();
}

void TukDriverDao::retireDriver(int driverId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE driver SET active = 0 WHERE id = :id");
    query.bindValue(":id", driverId);
    if (!query.exec())
    {
        qDebug () << "Unable to deactivate user: " << query.lastError().text();
        return;
    }

    query.prepare("UPDATE rickshaw_driver SET end_date = :date WHERE driver_id = :driverId");
    query.bindValue(":date", QDate::currentDate().toString(Qt::ISODate));
    query.bindValue(":driverId", driverId);
    if (!query.exec())
    {
        qDebug() << "Unable to update rickshaw_driver end_date: " << query.lastError().text();
    }
}

void TukDriverDao::activateDriver(int driverId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE driver SET active = 1 WHERE id = :id");
    query.bindValue(":id", driverId);
    if (!query.exec())
    {
        qDebug () << "Unable to activate user: " << query.lastError().text();
        return;
    }

    query.prepare("UPDATE rickshaw_driver SET end_date = :date WHERE driver_id = :driverId");
    query.bindValue(":date", QDate().toString(Qt::ISODate));
    query.bindValue(":driverId", driverId);
    if (!query.exec())
    {
        qDebug() << "Unable to update rickshaw_driver end_date: " << query.lastError().text();
    }
}

void TukDriverDao::removeDriver(int driverId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM driver WHERE id = :id");
    query.bindValue(":id", driverId);
    if (!query.exec())
        qDebug() << "Unable to remove driver: " << query.lastError().text();
}
