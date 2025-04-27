#include "corecontroller.h"
#include <QDebug>

CoreController::CoreController(TukTukListModel *tukListModel, QObject *parent)
    : QObject(parent)
    , tukTukListModel(*tukListModel)
{

}
