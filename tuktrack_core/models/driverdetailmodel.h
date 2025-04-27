#ifndef DRIVERDETAILMODEL_H
#define DRIVERDETAILMODEL_H

#include <QObject>
#include "tuktrack_core_global.h"
#include "data/tukdriver.h"
#include "data/tukdriversetting.h"

class TUKTRACK_CORE_EXPORT DriverDetailModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TukDriver *driver READ driver WRITE setDriver RESET resetDriver NOTIFY driverChanged FINAL)
    Q_PROPERTY(TukDriverSetting *driverSetting READ driverSetting WRITE setDriverSetting NOTIFY driverSettingChanged FINAL)
public:
    explicit DriverDetailModel(QObject *parent = nullptr);

    TukDriver *driver() const;
    void setDriver(TukDriver *newDriver);
    void resetDriver();

    TukDriverSetting *driverSetting() const;
    void setDriverSetting(TukDriverSetting *newDriverSetting);

public slots:
    void setCurrentDriverId(int id);

    void callDriver();

private:
    TukDriver *m_driver = nullptr;
    TukDriverSetting *m_driverSetting = nullptr;

signals:
    void driverChanged();
    void driverSettingChanged();
};

#endif // DRIVERDETAILMODEL_H
