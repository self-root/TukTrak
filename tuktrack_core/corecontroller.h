#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H

#include "tuktrack_core_global.h"
#include "models/tuktuklistmodel.h"
#include <QObject>

class TUKTRACK_CORE_EXPORT CoreController : public QObject
{
    Q_OBJECT
public:
    CoreController(TukTukListModel *tukListModel, QObject *parent = nullptr);
private:
    const TukTukListModel &tukTukListModel;
};

#endif // CORECONTROLLER_H
