#ifndef MAINTENANCETYPEMODEL_H
#define MAINTENANCETYPEMODEL_H

#include <QAbstractListModel>
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT MaintenanceTypeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles{
        MaintenanaceTypeRole = Qt::UserRole + 1,
        MaintenanceCountRole
    };
    explicit MaintenanceTypeModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void loadData();

private:
    QVector<QPair<QString, int>> maintenanceTypesList;

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // MAINTENANCETYPEMODEL_H
