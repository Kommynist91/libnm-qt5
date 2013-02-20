/*
    Copyright 2012-2013  Jan Grulich <jgrulich@redhat.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "pppoe.h"
#include "pppoe_p.h"

#include <nm-setting-pppoe.h>

#include <QtCore/QDebug>

NetworkManager::Settings::PppoeSettingPrivate::PppoeSettingPrivate():
    name(QString("pppoe")),
    service(QString()),
    username(QString()),
    password(QString()),
    passwordFlags(Setting::None)
{ }

NetworkManager::Settings::PppoeSetting::PppoeSetting():
    Setting(Setting::Pppoe),
    d_ptr(new PppoeSettingPrivate())
{ }

NetworkManager::Settings::PppoeSetting::PppoeSetting(PppoeSetting * setting):
    Setting(setting),
    d_ptr(new PppoeSettingPrivate())
{
    setService(setting->service());
    setUsername(setting->username());
    setPassword(setting->password());
    setPasswordFlags(setting->passwordFlags());
}

NetworkManager::Settings::PppoeSetting::~PppoeSetting()
{
    delete d_ptr;
}

QString NetworkManager::Settings::PppoeSetting::name() const
{
    Q_D(const PppoeSetting);

    return d->name;
}

void NetworkManager::Settings::PppoeSetting::setService(const QString& service)
{
    Q_D(PppoeSetting);

    d->service = service;
}

QString NetworkManager::Settings::PppoeSetting::service() const
{
    Q_D(const PppoeSetting);

    return d->service;
}

void NetworkManager::Settings::PppoeSetting::setUsername(const QString& username)
{
    Q_D(PppoeSetting);

    d->username = username;
}

QString NetworkManager::Settings::PppoeSetting::username() const
{
    Q_D(const PppoeSetting);

    return d->username;
}

void NetworkManager::Settings::PppoeSetting::setPassword(const QString& password)
{
    Q_D(PppoeSetting);

    d->password = password;
}

QString NetworkManager::Settings::PppoeSetting::password() const
{
    Q_D(const PppoeSetting);

    return d->password;
}

void NetworkManager::Settings::PppoeSetting::setPasswordFlags(NetworkManager::Settings::Setting::SecretFlagType flags)
{
    Q_D(PppoeSetting);

    d->passwordFlags = flags;
}

NetworkManager::Settings::Setting::SecretFlagType NetworkManager::Settings::PppoeSetting::passwordFlags() const
{
    Q_D(const PppoeSetting);

    return d->passwordFlags;
}

QStringList NetworkManager::Settings::PppoeSetting::needSecrets(bool requestNew) const
{
    QStringList secrets;

    if ((password().isEmpty() || requestNew) && passwordFlags() != Setting::NotRequired) {
        secrets << QLatin1String(NM_SETTING_PPPOE_PASSWORD);
    }

    return secrets;
}

void NetworkManager::Settings::PppoeSetting::secretsFromMap(const QVariantMap& secrets)
{
    if (secrets.contains(QLatin1String(NM_SETTING_PPPOE_PASSWORD))) {
        setPassword(secrets.value(QLatin1String(NM_SETTING_PPPOE_PASSWORD)).toString());
    }
}

QVariantMap NetworkManager::Settings::PppoeSetting::secretsToMap() const
{
    QVariantMap secrets;

    if (!password().isEmpty()) {
        secrets.insert(QLatin1String(NM_SETTING_PPPOE_PASSWORD), password());
    }

    return secrets;
}

void NetworkManager::Settings::PppoeSetting::fromMap(const QVariantMap& setting)
{
    if (setting.contains(QLatin1String(NM_SETTING_PPPOE_SERVICE))) {
        setService(setting.value(QLatin1String(NM_SETTING_PPPOE_SERVICE)).toString());
    }

    if (setting.contains(QLatin1String(NM_SETTING_PPPOE_USERNAME))) {
        setUsername(setting.value(QLatin1String(NM_SETTING_PPPOE_USERNAME)).toString());
    }

    if (setting.contains(QLatin1String(NM_SETTING_PPPOE_PASSWORD))) {
        setPassword(setting.value(QLatin1String(NM_SETTING_PPPOE_PASSWORD)).toString());
    }

    if (setting.contains(QLatin1String(NM_SETTING_PPPOE_PASSWORD_FLAGS))) {
        setPasswordFlags((Setting::SecretFlagType)setting.value(QLatin1String(NM_SETTING_PPPOE_PASSWORD_FLAGS)).toUInt());
    }
}

QVariantMap NetworkManager::Settings::PppoeSetting::toMap() const
{
    QVariantMap setting;

    if (!service().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_PPPOE_SERVICE), service());
    }

    if (!username().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_PPPOE_USERNAME), username());
    }

    if (!password().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_PPPOE_PASSWORD), password());
    }

    if (passwordFlags()) {
        setting.insert(QLatin1String(NM_SETTING_PPPOE_PASSWORD_FLAGS), passwordFlags());
    }

    return setting;
}

void NetworkManager::Settings::PppoeSetting::printSetting()
{
    NetworkManager::Settings::Setting::printSetting();

    qDebug() << NM_SETTING_PPPOE_SERVICE << ": " << service();
    qDebug() << NM_SETTING_PPPOE_USERNAME << ": " << username();
    qDebug() << NM_SETTING_PPPOE_PASSWORD << ": " << password();
    qDebug() << NM_SETTING_PPPOE_PASSWORD_FLAGS << ": " << passwordFlags();
}