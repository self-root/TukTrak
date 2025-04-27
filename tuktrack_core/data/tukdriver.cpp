#include "tukdriver.h"

TukDriver::TukDriver(QObject *parent)
    : QObject{parent}
{}

int TukDriver::id() const
{
    return m_id;
}

void TukDriver::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString TukDriver::lastName() const
{
    return m_lastName;
}

void TukDriver::setLastName(const QString &newLastName)
{
    if (m_lastName == newLastName)
        return;
    m_lastName = newLastName;
    emit lastNameChanged();
}

QString TukDriver::firstName() const
{
    return m_firstName;
}

void TukDriver::setFirstName(const QString &newFirstName)
{
    if (m_firstName == newFirstName)
        return;
    m_firstName = newFirstName;
    emit firstNameChanged();
}

QString TukDriver::idNumber() const
{
    return m_idNumber;
}

void TukDriver::setIdNumber(const QString &newIdNumber)
{
    if (m_idNumber == newIdNumber)
        return;
    m_idNumber = newIdNumber;
    emit idNumberChanged();
}

bool TukDriver::active() const
{
    return m_active;
}

void TukDriver::setActive(bool newActive)
{
    if (m_active == newActive)
        return;
    m_active = newActive;
    emit activeChanged();
}

QString TukDriver::phoneNumber() const
{
    return m_phoneNumber;
}

void TukDriver::setPhoneNumber(const QString &newPhoneNumber)
{
    if (m_phoneNumber == newPhoneNumber)
        return;
    m_phoneNumber = newPhoneNumber;
    emit phoneNumberChanged();
}

QString TukDriver::idPhoto() const
{
    return m_idPhoto;
}

void TukDriver::setIdPhoto(const QString &newIdPhoto)
{
    if (m_idPhoto == newIdPhoto)
        return;
    m_idPhoto = newIdPhoto;
    emit idPhotoChanged();
}

bool TukDriver::equal(const TukDriver &other) const
{
    return (m_id == other.id() &&
            m_lastName == other.lastName() &&
            m_firstName == other.firstName() &&
            m_idNumber == other.idNumber() &&
            m_phoneNumber == other.phoneNumber() &&
            m_active == other.active() &&
            m_idPhoto == other.idPhoto());
}
