#ifndef MAINTENANCECOSTBYTYPEMODEL_H
#define MAINTENANCECOSTBYTYPEMODEL_H

#include <QAbstractListModel>
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT MaintenanceCostByTypeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        MaintenanceType = Qt::UserRole + 1,
        CostRole
    };
    explicit MaintenanceCostByTypeModel(QObject *parent = nullptr);

    // Basic functionality:
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QVariant dataAt(int row, int role) const;

    Q_INVOKABLE void loadData(const QDate &startDate, const QDate &endDate);

private:
    QVector<QPair<QString, double>> maintenanceCost;
};

#endif // MAINTENANCECOSTBYTYPEMODEL_H
