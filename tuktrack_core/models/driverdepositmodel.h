#ifndef DRIVERDEPOSITMODEL_H
#define DRIVERDEPOSITMODEL_H

#include <QAbstractTableModel>
#include "tuktrack_core_global.h"
#include "data/driverdepositdao.h"

class TUKTRACK_CORE_EXPORT DriverDepositModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DepositListType{
        ByDriver,
        ByTukTuk
    };
    enum Roles{
        DateRole = Qt::UserRole + 1,
        AmountRole,
        RestAmountRole,
        NoteRole,
        HasDepositLeftRole,
        DriverName,
    };
    explicit DriverDepositModel(DepositListType depositListType = DepositListType::ByDriver, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


public slots:
    void loadDeposit(int driverId);
    void loadDeposit();
    void addDeposit(int driverId, int tukId, const QVariantMap data);
    void updateDeposit(int index, const QVariantMap data);
    void removeDeposit(int index);
    void setDriverId(int driverId);
    void setTukNumber(const QString &tukNumber);

private:
    DriverDepositList depositList;
    //DriverDepositSettingModel &depositSettingModel;
    DepositListType listType;
    int mDriverId = -1;
    QString mTukNumber;

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;

signals:
    void depositUpdated();
};

#endif // DRIVERDEPOSITMODEL_H
