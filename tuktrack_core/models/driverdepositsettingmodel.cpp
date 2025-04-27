#include "driverdepositsettingmodel.h"
#include "data/databaseaccessmanager.h"

DriverDepositSettingModel::DriverDepositSettingModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    depositSettingList = DepositSettingList(new std::vector<std::unique_ptr<DriverDepositSetting>>);
}

QVariant DriverDepositSettingModel::headerData(int section,
                                               Qt::Orientation orientation,
                                               int role) const
{
    if (orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0:
            return QString("Jour");
        case 1:
            return QString("Amount (Ar)");
        default:
            break;
        }
    }

    return QVariant();
}

int DriverDepositSettingModel::rowCount(const QModelIndex &parent) const
{
    return depositSettingList->size();
}

int DriverDepositSettingModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant DriverDepositSettingModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int column = index.column();
    DriverDepositSetting &depositSetting = *depositSettingList->at(index.row());
    if (role != Qt::DisplayRole)
        return QVariant();

        switch (column) {
        case 0:
            return DriverDepositSetting::WEEKDAY_NAME[depositSetting.dayOfWeek()];
        case 1:
            return depositSetting.amount();
        default:
            break;
        }

    return QVariant();
}

double DriverDepositSettingModel::expectedDepositFor(int weekDayNumber) const
{
    for (const std::unique_ptr<DriverDepositSetting> &deposit: *depositSettingList)
    {
        if (deposit->dayOfWeek() == weekDayNumber)
            return deposit->amount();
    }

    return 0;
}

void DriverDepositSettingModel::loadDriverDepositSetting(int driverId)
{
    beginResetModel();
    depositSettingList = DatabaseAccessManager::instance()->mDepositDao.getDepositSettings(driverId);
    std::sort(depositSettingList->begin(), depositSettingList->end(), [](std::unique_ptr<DriverDepositSetting> &a, std::unique_ptr<DriverDepositSetting> &b){
        return a->dayOfWeek() < b->dayOfWeek();
    });
    endResetModel();
}

void DriverDepositSettingModel::addDepositSettings(int driverId, const QStringList &daysOfWeek, double expectedAmount)
{
    for (const QString &weekDay : daysOfWeek)
    {
        int depositSettingId = weekDaySettingId(DriverDepositSetting::WEEKDAY_NUMBER[weekDay]);
        DriverDepositSetting setting;
        setting.setId(depositSettingId);
        setting.setAmount(expectedAmount);
        setting.setDayOfWeek(DriverDepositSetting::WEEKDAY_NUMBER[weekDay]);
        setting.setDriverId(driverId);
        if (depositSettingId > 0)
        {
            DatabaseAccessManager::instance()->mDepositDao.update(setting);
        }
        else{
            DatabaseAccessManager::instance()->mDepositDao.add(setting);
        }
    }

    loadDriverDepositSetting(driverId);
}

int DriverDepositSettingModel::weekDaySettingId(int weekDay) const
{
    for (int i = 0; i < depositSettingList->size(); i++)
    {
        if (depositSettingList->at(i)->dayOfWeek() == weekDay)
            return depositSettingList->at(i)->id();
    }

    return -1;
}


QHash<int, QByteArray> DriverDepositSettingModel::roleNames() const
{
    return QHash<int, QByteArray> {{Qt::DisplayRole, "display"}};
}
