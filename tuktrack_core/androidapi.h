#ifndef ANDROIDAPI_H
#define ANDROIDAPI_H

#include <QObject>

class AndroidApi : public QObject
{
    Q_OBJECT
public:
    explicit AndroidApi(QObject *parent = nullptr);
    static void dialNumber(const QString &number);

signals:
};

#endif // ANDROIDAPI_H
