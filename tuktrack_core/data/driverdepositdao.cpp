#include "driverdepositdao.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>

DriverDepositDao::DriverDepositDao(QSqlDatabase &database, QObject *parent)
    : mDatabase(database)
    , QObject{parent}
{}

DepositSettingList DriverDepositDao::getDepositSettings(int driverId) const
{
    DepositSettingList settingList(new std::vector<std::unique_ptr<DriverDepositSetting>>);

    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM driver_deposit_setting WHERE driver_id = :driver_id");
    query.bindValue(":driver_id", driverId);

    if (!query.exec())
    {
        qDebug() << "Unable to get driver deposit setting for: " << driverId << " Err: " << query.lastError().text();
        return settingList;
    }

    while (query.next())
    {
        std::unique_ptr<DriverDepositSetting> depositSetting(new DriverDepositSetting);

        depositSetting->setId(query.value("id").toInt());
        depositSetting->setDriverId(query.value("driver_id").toInt());
        depositSetting->setDayOfWeek(DriverDepositSetting::WEEKDAY_NUMBER[query.value("weekday").toString()]);
        depositSetting->setAmount(query.value("expected_amount").toDouble());
        settingList->push_back(std::move(depositSetting));
    }

    return settingList;
}

DriverDepositList DriverDepositDao::getDepositList(int driverId) const
{
    DriverDepositList depositList = DriverDepositList(new std::vector<std::unique_ptr<DriverDeposit>>);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM driver_deposit
        INNER JOIN driver ON driver.id = driver_deposit.driver_id
        INNER JOIN rickshaw ON rickshaw.id = driver_deposit.rickshaw_id
        WHERE driver_deposit.driver_id = :driverId
        ORDER BY driver_deposit.date DESC
    )");

    query.bindValue(":driverId", driverId);

    if (!query.exec())
    {
        qDebug() << "Unable to get driver depisits: " << query.lastError().text();
        return depositList;
    }

    while (query.next())
    {
        std::unique_ptr<DriverDeposit> deposit(new DriverDeposit);
        deposit->setId(query.value("driver_deposit.id").toInt());
        deposit->setDriverId(query.value("driver.id").toInt());
        deposit->setDriverName(query.value("driver.first_name").toString());
        deposit->setTukId(query.value("rickshaw.id").toInt());
        deposit->setTukNumber(query.value("rickshaw.registration_number").toString());
        deposit->setDateOfDeposit(QDate::fromString(query.value("driver_deposit.date").toString(), Qt::ISODate));
        deposit->setAmount(query.value("driver_deposit.amount_deposited").toDouble());
        deposit->setNote(query.value("driver_deposit.note").toString());
        depositList->push_back(std::move(deposit));
    }

    return depositList;
}

DriverDepositList DriverDepositDao::getDepositList(const QString &tukNumber)
{
    DriverDepositList depositList = DriverDepositList(new std::vector<std::unique_ptr<DriverDeposit>>);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM driver_deposit
        INNER JOIN driver ON driver.id = driver_deposit.driver_id
        INNER JOIN rickshaw ON rickshaw.id = driver_deposit.rickshaw_id
        WHERE rickshaw.registration_number = :tukNumber
        ORDER BY driver_deposit.date DESC
    )");

    query.bindValue(":tukNumber", tukNumber);

    if (!query.exec())
    {
        qDebug() << "Unable to get driver depisits: " << query.lastError().text();
        return depositList;
    }

    while (query.next())
    {
        std::unique_ptr<DriverDeposit> deposit(new DriverDeposit);
        deposit->setId(query.value("driver_deposit.id").toInt());
        deposit->setDriverId(query.value("driver.id").toInt());
        deposit->setDriverName(query.value("driver.first_name").toString());
        deposit->setTukId(query.value("rickshaw.id").toInt());
        deposit->setTukNumber(query.value("rickshaw.registration_number").toString());
        deposit->setDateOfDeposit(QDate::fromString(query.value("driver_deposit.date").toString(), Qt::ISODate));
        deposit->setAmount(query.value("driver_deposit.amount_deposited").toDouble());
        deposit->setNote(query.value("driver_deposit.note").toString());
        depositList->push_back(std::move(deposit));
    }

    return depositList;

}

DriverDepositList DriverDepositDao::getDepositList(const QDate &date) const
{
    DriverDepositList depositList = DriverDepositList(new std::vector<std::unique_ptr<DriverDeposit>>);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM driver_deposit
        INNER JOIN driver ON driver.id = driver_deposit.driver_id
        INNER JOIN rickshaw ON rickshaw.id = driver_deposit.rickshaw_id
        WHERE driver_deposit.date = :date
    )");

    query.bindValue(":date", date.toString(Qt::ISODate));

    if (!query.exec())
    {
        qDebug() << "Unable to get driver depisits: " << query.lastError().text();
        return depositList;
    }

    while (query.next())
    {
        std::unique_ptr<DriverDeposit> deposit(new DriverDeposit);
        deposit->setId(query.value("driver_deposit.id").toInt());
        deposit->setDriverId(query.value("driver.id").toInt());
        deposit->setDriverName(query.value("driver.first_name").toString());
        deposit->setTukId(query.value("rickshaw.id").toInt());
        deposit->setTukNumber(query.value("rickshaw.registration_number").toString());
        deposit->setDateOfDeposit(QDate::fromString(query.value("driver_deposit.date").toString(), Qt::ISODate));
        deposit->setAmount(query.value("driver_deposit.amount_deposited").toDouble());
        deposit->setNote(query.value("driver_deposit.note").toString());
        depositList->push_back(std::move(deposit));
    }

    return depositList;
}

DriverDepositList DriverDepositDao::getDepositList(const QDate &date, const QString &shift) const
{
    DriverDepositList depositList = DriverDepositList(new std::vector<std::unique_ptr<DriverDeposit>>);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM driver_deposit
        INNER JOIN driver ON driver.id = driver_deposit.driver_id
        INNER JOIN rickshaw ON rickshaw.id = driver_deposit.rickshaw_id
        INNER JOIN rickshaw_driver ON rickshaw_driver.driver_id = driver.id
        WHERE driver_deposit.date = :date AND rickshaw_driver.shift = :shift
    )");

    query.bindValue(":date", date.toString(Qt::ISODate));
    query.bindValue(":shift", shift);

    if (!query.exec())
    {
        qDebug() << "Unable to get driver depisits: " << query.lastError().text();
        return depositList;
    }

    while (query.next())
    {
        std::unique_ptr<DriverDeposit> deposit(new DriverDeposit);
        deposit->setId(query.value("driver_deposit.id").toInt());
        deposit->setDriverId(query.value("driver.id").toInt());
        deposit->setDriverName(query.value("driver.first_name").toString());
        deposit->setTukId(query.value("rickshaw.id").toInt());
        deposit->setTukNumber(query.value("rickshaw.registration_number").toString());
        deposit->setDateOfDeposit(QDate::fromString(query.value("driver_deposit.date").toString(), Qt::ISODate));
        deposit->setAmount(query.value("driver_deposit.amount_deposited").toDouble());
        deposit->setNote(query.value("driver_deposit.note").toString());
        depositList->push_back(std::move(deposit));
    }

    return depositList;
}

void DriverDepositDao::add(DriverDepositSetting &depositSetting) const
{
    QSqlQuery query(mDatabase);

    query.prepare(R"(
        INSERT INTO driver_deposit_setting(driver_id, weekday, expected_amount)
        VALUES(:driver_id, :weekday, :expected_amount)
    )");

    query.bindValue(":driver_id", depositSetting.driverId());
    query.bindValue(":weekday", DriverDepositSetting::WEEKDAY_NAME[depositSetting.dayOfWeek()]);
    query.bindValue(":expected_amount", depositSetting.amount());

    if (!query.exec())
    {
        qDebug() << "Unable to add driver deposit setting: " << query.lastError().text();
        return;
    }

    depositSetting.setId(query.lastInsertId().toInt());
}

void DriverDepositDao::add(DriverDeposit &deposit) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO driver_deposit(driver_id, rickshaw_id, date, amount_deposited, note)
        VALUES(:driver_id, :rickshaw_id, :date, :amount_deposited, :note)
    )");
    query.bindValue(":driver_id", deposit.driverId());
    query.bindValue(":rickshaw_id", deposit.tukId());
    query.bindValue(":date", deposit.DateOfDeposit());
    query.bindValue(":amount_deposited", deposit.amount());
    query.bindValue(":note", deposit.note());

    if (!query.exec())
    {
        qDebug() << "Failed to add deposit: " << query.lastError().text();
        return;
    }

    deposit.setId(query.lastInsertId().toInt());
}

void DriverDepositDao::update(const DriverDepositSetting &depositSetting) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE driver_deposit_setting
        SET expected_amount = :amount
        WHERE weekday = :weekday AND id = :id
    )");

    query.bindValue(":amount", depositSetting.amount());
    query.bindValue(":weekday", DriverDepositSetting::WEEKDAY_NAME[depositSetting.dayOfWeek()]);
    query.bindValue(":id", depositSetting.id());

    if (!query.exec())
        qDebug() << "Failed to update deposit setting: " << query.lastError().text();
}

void DriverDepositDao::update(const DriverDeposit &deposit) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE driver_deposit
        SET amount_deposited = :amount, note = :note
        WHERE id = :id
    )");
    query.bindValue(":amount", deposit.amount());
    query.bindValue(":note", deposit.note());
    query.bindValue(":id", deposit.id());

    if (!query.exec())
        qDebug() << "Unable to update driver deposit: " << query.lastError().text();
}

void DriverDepositDao::removeDeposit(int depositId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM driver_deposit WHERE id = :id");
    query.bindValue(":id", depositId);
    if (!query.exec())
        qDebug() << "Unable to delete deposit: " << query.lastError().text();
}

void DriverDepositDao::removeDepositSetting(int depositSettingId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM driver_deposit_setting WHERE id = :id");
    query.bindValue(":id", depositSettingId);
    if (!query.exec())
        qDebug() << "Unable to delete driver_deposit_setting: " << query.lastError().text();
}

double DriverDepositDao::expectedDepositAmount(int driverId, int weekDay) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT expected_amount
        FROM driver_deposit_setting
        WHERE driver_id = :driverId AND weekday = :weekday
    )");
    query.bindValue(":driverId", driverId);
    query.bindValue(":weekday", DriverDepositSetting::WEEKDAY_NAME[weekDay]);
    if (!query.exec())
    {
        qDebug() << "Could not get expected deposit amount" << query.lastError().text();
        return -1;
    }

    if (query.next())
        return query.value("expected_amount").toDouble();
    return -1;
}

double DriverDepositDao::totalRevenueBetween(const QDate &start, const QDate &end)
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT SUM(amount_deposited) AS total_revenue
        FROM driver_deposit
        WHERE date BETWEEN :startDate AND :endDate;
    )");
    query.bindValue(":startDate", start.toString(Qt::ISODate));
    query.bindValue(":endDate", end.toString(Qt::ISODate));
    if (!query.exec())
    {
        qDebug() << "Unable to get total revenue: " << query.lastError().text();
        return 0;
    }

    if(query.next())
        return query.value("total_revenue").toDouble();

    return 0;
}

QVector<QPair<QString, double>> DriverDepositDao::monthlyRevenueBetween(const QDate &startDate, const QDate &endDate)
{
    QVector<QPair<QString, double>> monthlyRevenue;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT
            strftime('%Y-%m', date) AS month,
            SUM(amount_deposited) AS total_revenue
        FROM
            driver_deposit
        WHERE
            date BETWEEN :startDate AND :endDate
        GROUP BY
            month
        ORDER BY
            month
    )");

    query.bindValue(":startDate", startDate.toString(Qt::ISODate));
    query.bindValue(":endDate", endDate.toString(Qt::ISODate));

    if (!query.exec())
    {
        qDebug() << "Could not get total monthly revenue: " << query.lastError().text();
        return monthlyRevenue;
    }

    while (query.next())
    {
        monthlyRevenue.push_back({query.value("month").toString(), query.value("total_revenue").toDouble()});
    }

    return monthlyRevenue;
}

QVector<QDate> DriverDepositDao::depositsDate() const
{
    QVector<QDate> dates;
    QSqlQuery query(mDatabase);
    QString queryString("SELECT date FROM driver_deposit GROUP BY date ORDER BY date DESC");
    if (!query.exec(queryString))
    {
        qDebug() << "Could not get depost date list: " << query.lastError().text();
        return dates;
    }

    while (query.next())
    {
        dates.push_back(QDate::fromString(query.value("date").toString(), Qt::ISODate));
    }
    return dates;
}

std::unique_ptr<DriverDeposit> DriverDepositDao::getDeposit(int driverId, const QDate &date) const
{
    std::unique_ptr<DriverDeposit> deposit(new DriverDeposit);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM driver_deposit
        INNER JOIN driver ON driver.id = driver_deposit.driver_id
        INNER JOIN rickshaw ON rickshaw.id = driver_deposit.rickshaw_id
        WHERE driver_deposit.driver_id = :driverId AND driver_deposit.date = :depositDate
        ORDER BY driver_deposit.date DESC
    )");

    query.bindValue(":driverId", driverId);
    query.bindValue(":depositDate", date.toString(Qt::ISODate));

    if (!query.exec())
    {
        qDebug() << "Unable to get driver depisits: " << query.lastError().text();
        return deposit;
    }

    if (query.next())
    {

        deposit->setId(query.value("driver_deposit.id").toInt());
        deposit->setDriverId(query.value("driver.id").toInt());
        deposit->setDriverName(query.value("driver.first_name").toString());
        deposit->setTukId(query.value("rickshaw.id").toInt());
        deposit->setTukNumber(query.value("rickshaw.registration_number").toString());
        deposit->setDateOfDeposit(QDate::fromString(query.value("driver_deposit.date").toString(), Qt::ISODate));
        deposit->setAmount(query.value("driver_deposit.amount_deposited").toDouble());
        deposit->setNote(query.value("driver_deposit.note").toString());
    }

    return deposit;
}
