#ifndef MAINTENANCELISTMODEL_H
#define MAINTENANCELISTMODEL_H

#include <QAbstractListModel>
#include "tuktrack_core_global.h"
#include "data/maintenancedao.h"

class TUKTRACK_CORE_EXPORT MaintenanceListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ListType{
        FutureMaintenace = 0,
        PastMaintenance,
        DateRange,
        All
    };
    enum Roles{
        IdRole = Qt::UserRole + 1,
        TukIdRole,
        TukNumberRole,
        MaintenanceTypeRole,
        DescriptionRole,
        ScheduleDateRole,
        PerformedDateRole,
        ReccuringRole,
        ReccurenceRole,
        CostRole
    };
    explicit MaintenanceListModel(ListType listType, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QDate startDate;

    QDate endDate;

protected:
    MaintenanceList maintenanceList;
    ListType mListType;
    int mTukId = -1;

public slots:
    void loadData();

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;
    void setTukId(int newTukId);

signals:
    void maintenanceListUpdated();
};

#endif // MAINTENANCELISTMODEL_H
