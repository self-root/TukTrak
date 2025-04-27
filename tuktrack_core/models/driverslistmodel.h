#ifndef DRIVERSLISTMODEL_H
#define DRIVERSLISTMODEL_H

#include <QAbstractListModel>
#include "../data/tukdriverdao.h"
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT DriversListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int activeDriversCount READ activeDriversCount WRITE setActiveDriversCount NOTIFY activeDriversCountChanged FINAL)
public:
    enum Roles{
        IdRole = Qt::UserRole + 1,
        FirstnameRole,
        LastnameRole,
        PhoneRole,
        IdNumberRole,
        ActiveRole,
        IdPhotoRole
    };
    explicit DriversListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int activeDriversCount() const;

    void setActiveDriversCount(int newActiveDriversCount);

private:
    TukDriverList driverList;
    int m_activeDriversCount = 0;

    void countActiveDriver();

public:
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void loadData();
    void loadData(int tukId);

    void addDriver(const QVariantMap &data);
    void updateDriver(int driverId, int driverSettingId, const QVariantMap &data);
    void retireDriver(int driverId);
    void activateDriver(int driverId);
    void removeDriver(int driverId);
signals:
    void activeDriversCountChanged();
    void driverRemoved(int driverId);
};

#endif // DRIVERSLISTMODEL_H
