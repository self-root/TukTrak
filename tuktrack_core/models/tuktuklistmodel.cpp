#include "tuktuklistmodel.h"
#include "../data/databaseaccessmanager.h"

TukTukListModel::TukTukListModel(QObject *parent)
    : QAbstractListModel(parent)
    , lists(TukTukList(new std::vector<std::unique_ptr<TukTuk>>))
{
    loadData();
}

int TukTukListModel::rowCount(const QModelIndex &parent) const
{
    return lists->size();
}

QVariant TukTukListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const TukTuk &tuk = *lists->at(index.row());
    switch (role) {
    case IdRole:
        return tuk.id();
    case PlateNumberRole:
        return tuk.registrationNumber();
    case ModelRole:
        return tuk.model();
    case PurchaseDateRole:
        return tuk.purchaseDate().toString("dd MMM yyyy");
    case StatusRole:
        return tuk.status();
    case PhaseRole:
        return tuk.phase();
    default:
        return QVariant();
    }

}

void TukTukListModel::loadData()
{
    beginResetModel();
    lists = DatabaseAccessManager::instance()->mTukTukDao.tuktuks();
    countActiveTukCount();
    endResetModel();
}

void TukTukListModel::addTukTuk(const QVariantMap &data)
{
    TukTuk tuk;
    tuk.setModel(data["model"].toString());
    tuk.setPhase(data["phase"].toInt());
    tuk.setPurchaseDate(data["purchaseDate"].toDate());
    tuk.setRegistrationNumber(data["registrationNumber"].toString());

    DatabaseAccessManager::instance()->mTukTukDao.add(tuk);
    loadData();
}

void TukTukListModel::updateTukTuk(int tukId, const QVariantMap &data)
{
    TukTuk tuk;
    tuk.setModel(data["model"].toString());
    tuk.setPhase(data["phase"].toInt());
    tuk.setPurchaseDate(data["purchaseDate"].toDate());
    tuk.setRegistrationNumber(data["registrationNumber"].toString());
    tuk.setId(tukId);
    DatabaseAccessManager::instance()->mTukTukDao.update(tuk);
    loadData();
}

int TukTukListModel::indexOf(const QString &plateNumber)
{
    for (int i = 0; i < lists->size(); i++)
    {
        if (lists->at(i)->registrationNumber() == plateNumber)
            return i;
    }

    return -1;
}

int TukTukListModel::tukIdOf(const QString &plateNumber)
{
    for (int i = 0; i < lists->size(); i++)
    {
        if (lists->at(i)->registrationNumber() == plateNumber)
            return lists->at(i)->id();
    }

    return -1;
}

void TukTukListModel::countActiveTukCount()
{
    int activeTuk = 0;
    for (const std::unique_ptr<TukTuk> &tuk: *lists)
    {
        if (tuk->status() == "active")
            activeTuk += 1;
    }
    setActiveTukCount(activeTuk);
}

int TukTukListModel::activeTukCount() const
{
    return m_activeTukCount;
}

void TukTukListModel::setActiveTukCount(int newActiveTukCount)
{
    if (m_activeTukCount == newActiveTukCount)
        return;
    m_activeTukCount = newActiveTukCount;
    emit activeTukCountChanged();
}


QHash<int, QByteArray> TukTukListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[PlateNumberRole] = "plateNumber";
    roles[ModelRole] = "tukModel";
    roles[PurchaseDateRole] = "purchaseDate";
    roles[StatusRole] = "status";
    roles[PhaseRole] = "phase";

    return roles;
}
