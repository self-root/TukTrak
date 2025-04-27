#include "tuktukdao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

TukTukDao::TukTukDao(QSqlDatabase &database, QObject *parent)
    : mDatabase(database)
    , QObject{parent}
{}

TukTukList TukTukDao::tuktuks() const
{
    TukTukList tuktukList(new std::vector<std::unique_ptr<TukTuk>>);
    QSqlQuery query(mDatabase);
    if(!query.exec("SELECT * FROM rickshaw ORDER BY id DESC"))
    {
        qDebug() << "Error while getting tuktuks from db: " << query.lastError().text();
        return tuktukList;
    }

    while (query.next())
    {
        std::unique_ptr<TukTuk> tuk(new TukTuk);
        tuk->setId(query.value("id").toInt());
        tuk->setRegistrationNumber(query.value("registration_number").toString());
        tuk->setModel(query.value("model").toString());
        tuk->setPurchaseDate(QDate::fromString(query.value("purchase_date").toString(), Qt::ISODate));
        tuk->setStatus(query.value("status").toString());
        tuk->setPhase(query.value("phase").toInt());

        tuktukList->push_back(std::move(tuk));
    }

    return tuktukList;

}

void TukTukDao::add(TukTuk &tuk) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO rickshaw(registration_number, model, purchase_date, status, phase)
        VALUES (:registration_number, :model, :purchase_date, :status, :phase)
    )");

    query.bindValue(":registration_number", tuk.registrationNumber());
    query.bindValue(":model", tuk.model());
    query.bindValue(":purchase_date", tuk.purchaseDate());
    query.bindValue(":status", tuk.status());
    query.bindValue(":phase", tuk.phase());

    if (!query.exec())
    {
        qDebug() << "Rickshaw insertion error: " << query.lastError().text();
        return;
    }
    tuk.setId(query.lastInsertId().toInt());

}

std::unique_ptr<TukTuk> TukTukDao::get(const QString &plateNumber) const
{
    std::unique_ptr<TukTuk> tuk(new TukTuk);
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM rickshaw WHERE registration_number = :plateNumber");
    query.bindValue(":plateNumber", plateNumber);
    if (!query.exec())
    {
        qDebug() << "Unable to get tuktuk by plateNumber: " << query.lastError().text();
        return tuk;
    }
    if (query.next())
    {
        tuk->setId(query.value("id").toInt());
        tuk->setRegistrationNumber(query.value("registration_number").toString());
        tuk->setModel(query.value("model").toString());
        tuk->setPurchaseDate(QDate::fromString(query.value("purchase_date").toString(), Qt::ISODate));
        tuk->setStatus(query.value("status").toString());
        tuk->setPhase(query.value("phase").toInt());
    }
    return tuk;
}

int TukTukDao::getId(const QString &plateNumber) const
{
    QSqlQuery query(mDatabase);
    query.prepare("SELECT id FROM rickshaw WHERE registration_number = :plateNumber");
    query.bindValue(":plateNumber", plateNumber);

    if (query.exec())
        if (query.next())
            return query.value("id").toInt();
        else {
            return -1;
        }
    else {
        qDebug() << "Error while getting rickshaw ID from db: " << query.lastError().text();
        return -1;
    }

}

void TukTukDao::update(const TukTuk &tukTuk) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE rickshaw
        SET registration_number = :number,
            model = :model,
            purchase_date = :date,
            phase = :phase
        WHERE id = :id
    )");

    query.bindValue(":number", tukTuk.registrationNumber());
    query.bindValue(":model", tukTuk.model());
    query.bindValue(":date", tukTuk.purchaseDate());
    query.bindValue(":phase", tukTuk.phase());
    query.bindValue(":id", tukTuk.id());

    if (!query.exec())
        qDebug() << "Unable to update TukTuk: " << query.lastError().text();

}

void TukTukDao::remove(int tukId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM rickshaw WHERE id = :id");
    query.bindValue(":id", tukId);

    if (!query.exec())
        qDebug() << "Unable to remove Tuktuk: " << query.lastError().text();
}

void TukTukDao::changeStatus(int tukId, const QString status) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE rickshaw
        SET status = :status
        WHERE id = :id
    )");

    query.bindValue(":status", status);
    query.bindValue(":id", tukId);
    if(!query.exec())
        qDebug() << "Could not change tuktuk status: " << query.lastError().text();
}
