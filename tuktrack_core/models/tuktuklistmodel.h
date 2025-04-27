#ifndef TUKTUKLISTMODEL_H
#define TUKTUKLISTMODEL_H

#include <QAbstractListModel>
#include "tuktrack_core_global.h"
#include "../data/tuktukdao.h"

class TUKTRACK_CORE_EXPORT TukTukListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int activeTukCount READ activeTukCount WRITE setActiveTukCount NOTIFY activeTukCountChanged FINAL)
public:
    enum Roles{
        IdRole = Qt::UserRole + 1,
        PlateNumberRole,
        ModelRole,
        PurchaseDateRole,
        StatusRole,
        PhaseRole
    };
    explicit TukTukListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int activeTukCount() const;
    void setActiveTukCount(int newActiveTukCount);

public slots:
    void loadData();
    void addTukTuk(const QVariantMap &data);
    void updateTukTuk(int tukId, const QVariantMap &data);
    int indexOf(const QString &plateNumber);
    int tukIdOf(const QString &plateNumber);

private:
    TukTukList lists;
    int m_activeTukCount = 0;
    void countActiveTukCount();

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;

signals:
    void activeTukCountChanged();
};

#endif // TUKTUKLISTMODEL_H
