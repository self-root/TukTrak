#ifndef TUKDRIVER_H
#define TUKDRIVER_H

#include <QObject>
#include "tuktrack_core_global.h"

class TUKTRACK_CORE_EXPORT TukDriver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)

    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged FINAL)

    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged FINAL)

    Q_PROPERTY(QString idNumber READ idNumber WRITE setIdNumber NOTIFY idNumberChanged FINAL)

    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged FINAL)

    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged FINAL)

    Q_PROPERTY(QString idPhoto READ idPhoto WRITE setIdPhoto NOTIFY idPhotoChanged FINAL)

public:
    explicit TukDriver(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    QString lastName() const;
    void setLastName(const QString &newLastName);

    QString firstName() const;
    void setFirstName(const QString &newFirstName);

    QString idNumber() const;
    void setIdNumber(const QString &newIdNumber);

    bool active() const;
    void setActive(bool newActive);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &newPhoneNumber);

    QString idPhoto() const;
    void setIdPhoto(const QString &newIdPhoto);

    bool equal(const TukDriver &other) const;

private:
    int m_id = -1;
    QString m_lastName;
    QString m_firstName;
    QString m_idNumber;
    QString m_phoneNumber;
    bool m_active = true;
    QString m_idPhoto;

signals:
    void idChanged();
    void lastNameChanged();
    void firstNameChanged();
    void idNumberChanged();
    void activeChanged();
    void phoneNumberChanged();
    void idPhotoChanged();
};

#endif // TUKDRIVER_H
