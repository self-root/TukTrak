#ifndef DRIVERDEPOSITSETTINGMODEL_H
#define DRIVERDEPOSITSETTINGMODEL_H

#include <QAbstractTableModel>
#include "data/driverdepositdao.h"

class DriverDepositSettingModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DriverDepositSettingModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    double expectedDepositFor(int weekDayNumber) const;

public slots:
    void loadDriverDepositSetting(int driverId);
    void addDepositSettings(int driverId, const QStringList &daysOfWeek, double expectedAmount);

private:
    DepositSettingList depositSettingList;

    int weekDaySettingId(int weekDay) const;

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // DRIVERDEPOSITSETTINGMODEL_H
