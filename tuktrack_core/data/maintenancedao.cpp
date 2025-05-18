#include "maintenancedao.h"
#include <QSqlQuery>
#include <QSqlError>

MaintenanceDao::MaintenanceDao(QSqlDatabase &database, QObject *parent)
    : mDatabase(database)
    , QObject{parent}
{}

void MaintenanceDao::add(TukMaintenance &maintenance) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO maintenance(maintenance_type, description, scheduled_date, performed_date, is_recurring, recurrence_days, cost, rickshaw_id)
        VALUES (:maintenance_type, :description, :scheduled_date, :performed_date,:is_recurring, :recurrence_days, :cost, :rickshaw_id)
    )");
    query.bindValue(":maintenance_type", maintenance.maintenanceType());
    query.bindValue(":description", maintenance.description());
    query.bindValue(":scheduled_date", maintenance.scheduledDate().toString(Qt::ISODate));
    query.bindValue(":performed_date", maintenance.performedDate().toString(Qt::ISODate));
    query.bindValue(":is_recurring", maintenance.reccuring());
    query.bindValue(":recurrence_days", maintenance.reccurenceDays());
    query.bindValue(":cost", maintenance.cost());
    query.bindValue(":rickshaw_id", maintenance.tukId());

    if (!query.exec())
    {
        qDebug() << "Could not add maintenance to database: " << query.lastError().text();
        return;
    }

    maintenance.setId(query.lastInsertId().toInt());
}

void MaintenanceDao::update(const TukMaintenance &maintenance) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE maintenance
        SET maintenance_type = :type,
            description = :description,
            scheduled_date = :scheduled_date,
            performed_date = :performed_date,
            is_recurring = :is_recurring,
            recurrence_days = :recurrence_days,
            cost = :cost
        WHERE id = :id
    )");

    query.bindValue(":type", maintenance.maintenanceType());
    query.bindValue(":description", maintenance.description());
    query.bindValue(":scheduled_date", maintenance.scheduledDate().toString(Qt::ISODate));
    query.bindValue(":performed_date", maintenance.performedDate().toString(Qt::ISODate));
    query.bindValue(":is_recurring", maintenance.reccuring());
    query.bindValue(":recurrence_days", maintenance.reccurenceDays());
    query.bindValue(":cost", maintenance.cost());
    query.bindValue(":id", maintenance.id());

    if (!query.exec())
        qDebug() << "Could not update maintenance: " << query.lastError().text();
}

std::unique_ptr<TukMaintenance> MaintenanceDao::get(int maintenanceId) const
{
    std::unique_ptr<TukMaintenance> maintenance(new TukMaintenance);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM maintenance
        INNER JOIN rickshaw ON rickshaw_id = rickshaw.id
        WHERE id = :id
    )");

    query.bindValue(":id", maintenanceId);
    if (!query.exec())
    {
        qDebug() << "Could not get TukMaintenance fro db: " << query.lastError().text();
        return maintenance;
    }

    if (query.next())
    {
        maintenance->setId(maintenanceId);
        maintenance->setMaintenanceType(query.value("maintenance_type").toString());
        maintenance->setDescription(query.value("description").toString());
        maintenance->setScheduledDate(QDate::fromString(query.value("scheduled_date").toString(), Qt::ISODate));
        maintenance->setPerformedDate(QDate::fromString(query.value("performed_date").toString(), Qt::ISODate));
        maintenance->setReccuring(query.value("is_recurring").toBool());
        maintenance->setReccurenceDays(query.value("recurrence_days").toInt());
        maintenance->setCost(query.value("cost").toDouble());
        maintenance->setTukNumber(query.value("rickshaw.registration_number").toString());
        maintenance->setTukId(query.value("rickshaw.id").toInt());
    }

    return maintenance;

}

void MaintenanceDao::remove(int maintenanceId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM maintenance WHERE id = :id");
    query.bindValue(":id", maintenanceId);

    if (!query.exec())
        qDebug() << "Could not remove maintenance: " << query.lastError().text();
}

MaintenanceList MaintenanceDao::getScheduledMaintenances() const
{
    //QDate today = QDate::currentDate();
    MaintenanceList list(new std::vector<std::unique_ptr<TukMaintenance>>);
    QSqlQuery query(mDatabase);
    QString queryString (R"(
        SELECT * FROM maintenance
        INNER JOIN rickshaw ON rickshaw_id = rickshaw.id
        WHERE performed_date IS NULL
        ORDER BY scheduled_date ASC
    )");
    //query.bindValue(":today", today.toString(Qt::ISODate));

    if (!query.exec(queryString))
    {
        qDebug() << "Could not get TukMaintenance list fro db: " << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        std::unique_ptr<TukMaintenance> maintenance(new TukMaintenance);
        maintenance->setId(query.value("maintenance.id").toInt());
        maintenance->setMaintenanceType(query.value("maintenance_type").toString());
        maintenance->setDescription(query.value("description").toString());
        maintenance->setScheduledDate(QDate::fromString(query.value("scheduled_date").toString(), Qt::ISODate));
        maintenance->setPerformedDate(QDate::fromString(query.value("performed_date").toString(), Qt::ISODate));
        maintenance->setReccuring(query.value("is_recurring").toBool());
        maintenance->setReccurenceDays(query.value("recurrence_days").toInt());
        maintenance->setCost(query.value("cost").toDouble());
        maintenance->setTukNumber(query.value("rickshaw.registration_number").toString());
        maintenance->setTukId(query.value("rickshaw.id").toInt());

        list->push_back(std::move(maintenance));
    }

    return list;
}

MaintenanceList MaintenanceDao::getScheduledMaintenances(int tukId) const
{
    //QDate today = QDate::currentDate();
    MaintenanceList list(new std::vector<std::unique_ptr<TukMaintenance>>);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM maintenance
        INNER JOIN rickshaw ON rickshaw_id = rickshaw.id
        WHERE rickshaw_id = :id AND performed_date IS NULL
    )");


    query.bindValue(":id", tukId);
    //query.bindValue(":today", today.toString(Qt::ISODate));

    if (!query.exec())
    {
        qDebug() << "Could not get TukMaintenance list fro db: " << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        std::unique_ptr<TukMaintenance> maintenance(new TukMaintenance);
        maintenance->setId(query.value("maintenance.id").toInt());
        maintenance->setMaintenanceType(query.value("maintenance_type").toString());
        maintenance->setDescription(query.value("description").toString());
        maintenance->setScheduledDate(QDate::fromString(query.value("scheduled_date").toString(), Qt::ISODate));
        maintenance->setPerformedDate(QDate::fromString(query.value("performed_date").toString(), Qt::ISODate));
        maintenance->setReccuring(query.value("is_recurring").toBool());
        maintenance->setReccurenceDays(query.value("recurrence_days").toInt());
        maintenance->setCost(query.value("cost").toDouble());
        maintenance->setTukNumber(query.value("rickshaw.registration_number").toString());
        maintenance->setTukId(query.value("rickshaw.id").toInt());
        list->push_back(std::move(maintenance));
    }

    return list;
}

MaintenanceList MaintenanceDao::getPastMaintenances() const
{
    QDate today = QDate::currentDate();
    MaintenanceList list(new std::vector<std::unique_ptr<TukMaintenance>>);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM maintenance
        INNER JOIN rickshaw ON rickshaw_id = rickshaw.id
        WHERE performed_date <= :today
    )");
    query.bindValue(":today", today.toString(Qt::ISODate));

    if (!query.exec())
    {
        qDebug() << "Could not get TukMaintenance list fro db: " << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        std::unique_ptr<TukMaintenance> maintenance(new TukMaintenance);
        maintenance->setId(query.value("maintenance.id").toInt());
        maintenance->setMaintenanceType(query.value("maintenance_type").toString());
        maintenance->setDescription(query.value("description").toString());
        maintenance->setScheduledDate(QDate::fromString(query.value("scheduled_date").toString(), Qt::ISODate));
        maintenance->setPerformedDate(QDate::fromString(query.value("performed_date").toString(), Qt::ISODate));
        maintenance->setReccuring(query.value("is_recurring").toBool());
        maintenance->setReccurenceDays(query.value("recurrence_days").toInt());
        maintenance->setCost(query.value("cost").toDouble());
        maintenance->setTukNumber(query.value("rickshaw.registration_number").toString());
        maintenance->setTukId(query.value("rickshaw.id").toInt());

        list->push_back(std::move(maintenance));
    }

    return list;
}

MaintenanceList MaintenanceDao::getPastMaintenances(int tukId) const
{
    QDate today = QDate::currentDate();
    MaintenanceList list(new std::vector<std::unique_ptr<TukMaintenance>>);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM maintenance
        INNER JOIN rickshaw ON rickshaw_id = rickshaw.id
        WHERE performed_date <= :today AND rickshaw_id = :tukId
    )");
    query.bindValue(":today", today.toString(Qt::ISODate));
    query.bindValue(":tukId", tukId);

    if (!query.exec())
    {
        qDebug() << "Could not get TukMaintenance list fro db: " << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        std::unique_ptr<TukMaintenance> maintenance(new TukMaintenance);
        maintenance->setId(query.value("maintenance.id").toInt());
        maintenance->setMaintenanceType(query.value("maintenance_type").toString());
        maintenance->setDescription(query.value("description").toString());
        maintenance->setScheduledDate(QDate::fromString(query.value("scheduled_date").toString(), Qt::ISODate));
        maintenance->setPerformedDate(QDate::fromString(query.value("performed_date").toString(), Qt::ISODate));
        maintenance->setReccuring(query.value("is_recurring").toBool());
        maintenance->setReccurenceDays(query.value("recurrence_days").toInt());
        maintenance->setCost(query.value("cost").toDouble());
        maintenance->setTukNumber(query.value("rickshaw.registration_number").toString());
        maintenance->setTukId(query.value("rickshaw.id").toInt());

        list->push_back(std::move(maintenance));
    }

    return list;
}

MaintenanceList MaintenanceDao::getPastMaintenances(const QDate &startDate, const QDate &endDate) const
{
    QDate today = QDate::currentDate();
    MaintenanceList list(new std::vector<std::unique_ptr<TukMaintenance>>);
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM maintenance
        INNER JOIN rickshaw ON rickshaw_id = rickshaw.id
        WHERE performed_date BETWEEN :startDate AND :endDate
        ORDER BY performed_date DESC
    )");
    query.bindValue(":startDate", startDate.toString(Qt::ISODate));
    query.bindValue(":endDate", endDate.toString(Qt::ISODate));

    if (!query.exec())
    {
        qDebug() << "Could not get TukMaintenance list fro db: " << query.lastError().text();
        return list;
    }

    while (query.next())
    {
        std::unique_ptr<TukMaintenance> maintenance(new TukMaintenance);
        maintenance->setId(query.value("maintenance.id").toInt());
        maintenance->setMaintenanceType(query.value("maintenance_type").toString());
        maintenance->setDescription(query.value("description").toString());
        maintenance->setScheduledDate(QDate::fromString(query.value("scheduled_date").toString(), Qt::ISODate));
        maintenance->setPerformedDate(QDate::fromString(query.value("performed_date").toString(), Qt::ISODate));
        maintenance->setReccuring(query.value("is_recurring").toBool());
        maintenance->setReccurenceDays(query.value("recurrence_days").toInt());
        maintenance->setCost(query.value("cost").toDouble());
        maintenance->setTukNumber(query.value("rickshaw.registration_number").toString());
        maintenance->setTukId(query.value("rickshaw.id").toInt());

        list->push_back(std::move(maintenance));
    }

    return list;
}

double MaintenanceDao::maintenanceCostBetween(const QDate &startDate, const QDate &endDate)
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT SUM(cost) AS total_expense
        FROM maintenance
        WHERE performed_date BETWEEN :startDate AND :endDate
    )");
    query.bindValue(":startDate", startDate.toString(Qt::ISODate));
    query.bindValue(":endDate", endDate.toString(Qt::ISODate));

    if(!query.exec())
    {
        qDebug() << "Unable to get total expenses: " << query.lastError().text();
        return 0;
    }

    if (query.next())
        return query.value("total_expense").toDouble();

    return 0;
}

QVector<QPair<QString, double> > MaintenanceDao::monthlyMaintenanceCostBetween(const QDate &startDate, const QDate &endDate)
{
    QVector<QPair<QString, double>> monthlyRevenue;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT
            strftime('%Y-%m', performed_date) AS month,
            SUM(cost) AS total_cost
        FROM
            maintenance
        WHERE
            performed_date BETWEEN :startDate AND :endDate
        GROUP BY
            month
        ORDER BY
            month
    )");

    query.bindValue(":startDate", startDate.toString(Qt::ISODate));
    query.bindValue(":endDate", endDate.toString(Qt::ISODate));

    if (!query.exec())
    {
        qDebug() << "Could not get total monthly maintenance cost: " << query.lastError().text();
        return monthlyRevenue;
    }

    while (query.next())
    {
        monthlyRevenue.push_back({query.value("month").toString(), query.value("total_cost").toDouble()});
    }

    return monthlyRevenue;
}

QVector<QPair<QString, int> > MaintenanceDao::getMaintenanceTypes()
{
    QVector<QPair<QString, int> > maintenanceTypes;
    QSqlQuery query(mDatabase);
    QString queryString = R"(
        SELECT
            COUNT(LOWER(maintenance_type)) AS occurence, maintenance_type
        FROM
            maintenance
        GROUP BY
            LOWER(maintenance_type)
        ORDER BY
            occurence DESC
    )";
    if (!query.exec(queryString))
        qDebug() << "Unable to get maintenance types from db: " << query.lastError().text();

    while (query.next())
    {
        maintenanceTypes.push_back(
            {
                query.value("maintenance_type").toString(),
                query.value("occurence").toInt()
            }
        );
    }

    return maintenanceTypes;
}

QVector<QPair<QString, double> > MaintenanceDao::maintenanceCostByTukTuk(const QDate &startDate, const QDate &endDate)
{
    QVector<QPair<QString, double>> maintenanceCost;

    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT registration_number, SUM(cost) AS total_cost FROM maintenance
        INNER JOIN rickshaw ON rickshaw.id = maintenance.rickshaw_id
        WHERE performed_date BETWEEN :startDate AND :endDate
        GROUP BY registration_number
        ORDER BY total_cost ASC
    )");
    query.bindValue(":startDate", startDate.toString(Qt::ISODate));
    query.bindValue(":endDate", endDate.toString(Qt::ISODate));

    if (!query.exec())
        qDebug() << "Error getting maintenance cost by tuctuc: " << query.lastError().text();

    while (query.next()) {
        maintenanceCost.push_back({query.value("registration_number").toString(), query.value("total_cost").toDouble()});
    }

    return maintenanceCost;
}

QVector<QPair<QString, double> > MaintenanceDao::maintenanceCostByType(const QDate &startDate, const QDate &endDate)
{
    QVector<QPair<QString, double>> maintenanceCost;

    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT maintenance_type, SUM(cost) AS total_cost FROM maintenance
        WHERE performed_date BETWEEN :startDate AND :endDate
        GROUP BY maintenance_type
        ORDER BY total_cost ASC
    )");
    query.bindValue(":startDate", startDate.toString(Qt::ISODate));
    query.bindValue(":endDate", endDate.toString(Qt::ISODate));

    if (!query.exec())
        qDebug() << "Error getting maintenance cost by type: " << query.lastError().text();

    while (query.next()) {
        maintenanceCost.push_back({query.value("maintenance_type").toString(), query.value("total_cost").toDouble()});
    }

    return maintenanceCost;
}
