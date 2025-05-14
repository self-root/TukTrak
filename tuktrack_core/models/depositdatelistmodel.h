#ifndef DEPOSITDATELISTMODEL_H
#define DEPOSITDATELISTMODEL_H

#include <QAbstractListModel>
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT DepositDateListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles{
        DateRole = Qt::UserRole + 1,
    };
    explicit DepositDateListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void loadData();
    QDate dateAt(int index);

private:
    QVector<QDate> depositsDate;

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // DEPOSITDATELISTMODEL_H
