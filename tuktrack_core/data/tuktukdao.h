#ifndef TUKTUKDAO_H
#define TUKTUKDAO_H

#include <QObject>

#include "tuktrack_core_global.h"
#include "tuktuk.h"

typedef std::unique_ptr<std::vector<std::unique_ptr<TukTuk>>> TukTukList;

class QSqlDatabase;

class TUKTRACK_CORE_EXPORT TukTukDao : public QObject
{
    Q_OBJECT
public:
    explicit TukTukDao(QSqlDatabase &database, QObject *parent = nullptr);

    TukTukList tuktuks() const;
    void add(TukTuk &tuk) const;
    std::unique_ptr<TukTuk> get(const QString &plateNumber) const;
    int getId(const QString &plateNumber) const;
    void update(const TukTuk &tukTuk) const;
    void remove(int tukId) const;
    void changeStatus(int tukId, const QString status) const;
private:
    QSqlDatabase &mDatabase;

signals:
};

#endif // TUKTUKDAO_H
