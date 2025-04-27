#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QObject>

class UiController : public QObject
{
    Q_OBJECT
public:
    explicit UiController(QObject *parent = nullptr);

signals:
    void goDriverDetails();
    void goBack();
    void goTukDetail();
};

#endif // UICONTROLLER_H
