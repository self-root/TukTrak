#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStyleHints>
#include "corecontroller.h"
#include "uicontroller.h"
#include "models/driverslistmodel.h"
#include "models/driverdetailmodel.h"
#include "models/driverdepositsettingmodel.h"
#include "models/driverdepositmodel.h"
#include "models/tukdetailmodel.h"
#include "models/dashboardmodel.h"
//#include "models/dailydepositlistmodel.h"
#include "models/depositdatelistmodel.h"
#include "models/dailydepositmodels.h"
//#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.styleHints()->setMousePressAndHoldInterval(200);
    QCoreApplication::setOrganizationName("iroot");
    QCoreApplication::setApplicationName("TukTrack");
    TukTukListModel tukListModel;
    DriversListModel driverListModel;
    DriverDetailModel driverDetailModel;
    DriverDepositSettingModel depositSettingListModel;
    DriverDepositModel depositListModel;
    TukDetailModel tukDetailModel;
    DepositDateListModel depositDateList;
    DailyDepositModels dailyDepositModels;
    CoreController controller(&tukListModel);
    DashboardModel dashboardModel(driverListModel, tukListModel, depositListModel, tukDetailModel);
    UiController uiController;
    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("controller", &controller);
    context->setContextProperty("tukListModel", &tukListModel);
    context->setContextProperty("driverListModel", &driverListModel);
    context->setContextProperty("depositListModel", &depositListModel);
    context->setContextProperty("driverDetail", &driverDetailModel);
    context->setContextProperty("uiController", &uiController);
    context->setContextProperty("depositSettingListModel", &depositSettingListModel);
    context->setContextProperty("tukDetailModel", &tukDetailModel);
    context->setContextProperty("dashboardModel", &dashboardModel);
    context->setContextProperty("depositDateList", &depositDateList);
    context->setContextProperty("dailyDepositModels", &dailyDepositModels);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("TukTrack", "Main");

    return app.exec();
}
