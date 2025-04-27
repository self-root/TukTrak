#ifndef REVENUECHARTMODEL_H
#define REVENUECHARTMODEL_H

#include <QObject>
#include <QPair>
#include <QMap>

class RevenueChartModel : public QObject
{
    Q_OBJECT
public:
    struct Data
    {
        double expense = 0;
        double revenue = 0;
    };
    explicit RevenueChartModel(QObject *parent = nullptr);
    enum Roles{
        MonthRole = Qt::UserRole + 1,
        RevenueRole,
        ExpenseRole,
        ColorRole
    };
    Q_INVOKABLE int rowSize();

    Q_INVOKABLE QVariant dataAt(int index, int role) const;

    Q_INVOKABLE void loadData();

private:
    QMap<QString, Data> mapData;
signals:
};

#endif // REVENUECHARTMODEL_H
