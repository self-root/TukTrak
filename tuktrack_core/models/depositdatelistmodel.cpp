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

void DepositDateListModel::loadDate()
{
    beginResetModel();
    depositsDate = DatabaseAccessManager::instance()->mDepositDao.depositsDate();
    endResetModel();
}


QHash<int, QByteArray> DepositDateListModel::roleNames() const
{
    return {{Roles::DateRole, "depositDate"}};
}
