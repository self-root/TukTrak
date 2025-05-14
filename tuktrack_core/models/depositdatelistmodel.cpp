#include "depositdatelistmodel.h"
#include "data/databaseaccessmanager.h"
#include <QDate>

DepositDateListModel::DepositDateListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int DepositDateListModel::rowCount(const QModelIndex &parent) const
{
    return depositsDate.size();
}

QVariant DepositDateListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == DateRole)
        return depositsDate.at(index.row());
    return QVariant();
}

void DepositDateListModel::loadData()
{
    beginResetModel();
    depositsDate = DatabaseAccessManager::instance()->mDepositDao.depositsDate();
    endResetModel();
}

QDate DepositDateListModel::dateAt(int index)
{
    if (index >= 0 && index < depositsDate.size())
    {
        return depositsDate.at(index);
    }
    return QDate();
}


QHash<int, QByteArray> DepositDateListModel::roleNames() const
{
    return {{Roles::DateRole, "depositDate"}};
}
