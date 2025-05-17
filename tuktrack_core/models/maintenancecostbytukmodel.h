#ifndef MAINTENANCECOSTBYTUKMODEL_H
#define MAINTENANCECOSTBYTUKMODEL_H

#include <QAbstractListModel>
#include <QPair>
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT MaintenanceCostByTukModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles{
        TukNumberRole = Qt::UserRole + 1,
        CostRole
    };
    explicit MaintenanceCostByTukModel(QObject *parent = nullptr);

    // Basic functionality:
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QVariant dataAt(int row, int role);

    Q_INVOKABLE void loadData(const QDate &startDate, const QDate &endDate);

private:
    QVector<QPair<QString, double>> maintenanceCostByTuc;
};

#endif // MAINTENANCECOSTBYTUKMODEL_H
