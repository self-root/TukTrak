#ifndef TUKDRIVERSHIFTMODEL_H
#define TUKDRIVERSHIFTMODEL_H

#include <QAbstractListModel>
#include "tuktrack_core_global.h"
#include "data/tukdriverdao.h"

class TUKTRACK_CORE_EXPORT TukDriverShiftModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles{
        NameRole = Qt::UserRole + 1,
        ShiftRole,
        ActiveRole,
    };
    explicit TukDriverShiftModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void getDrivers(int tukId);

private:
    TukDriverList drivers;

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // TUKDRIVERSHIFTMODEL_H
