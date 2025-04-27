#include "androidapi.h"
#include <QCoreApplication>

AndroidApi::AndroidApi(QObject *parent)
    : QObject{parent}
{}

void AndroidApi::dialNumber(const QString &number)
{
    QString numberUri = "tel:" + number;
    QJniObject numberUriObj = QJniObject::fromString(numberUri);
    QJniObject context = QNativeInterface::QAndroidApplication::context();
    QJniObject::callStaticMethod<void>(
        "org/iroot/tuktrack/AndroidInterface",
        "dialNumber",
        "(Landroid/content/Context;Ljava/lang/String;)V",
        context,
        numberUriObj);
}
