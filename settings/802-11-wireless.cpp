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

#include "802-11-wireless.h"
#include "802-11-wireless_p.h"

#include <nm-setting-wireless.h>

#include <QtCore/QDebug>

NetworkManager::Settings::WirelessSettingPrivate::WirelessSettingPrivate():
    name(QString("802-11-wireless")),
    ssid(QByteArray()),
    mode(NetworkManager::Settings::WirelessSetting::Infrastructure),
    band(WirelessSetting::Automatic),
    channel(0),
    bssid(QByteArray()),
    rate(0),
    txPower(0),
    macAddress(QByteArray()),
    clonedMacAddress(QByteArray()),
    macAddressBlacklist(QStringList()),
    mtu(0),
    seenBssids(QStringList()),
    security(QString()),
    hidden(false)
{ }

NetworkManager::Settings::WirelessSetting::WirelessSetting():
    Setting(Setting::Wireless),
    d_ptr(new WirelessSettingPrivate())
{ }

NetworkManager::Settings::WirelessSetting::WirelessSetting(NetworkManager::Settings::WirelessSetting* setting):
    Setting(setting),
    d_ptr(new WirelessSettingPrivate())
{
    setSsid(setting->ssid());
    setMode(setting->mode());
    setBand(setting->band());
    setChannel(setting->channel());
    setBssid(setting->bssid());
    setRate(setting->rate());
    setTxPower(setting->txPower());
    setMacAddress(setting->macAddress());
    setClonedMacAddress(setting->clonedMacAddress());
    setMacAddressBlacklist(setting->macAddressBlacklist());
    setMtu(setting->mtu());
    setSeenBssids(setting->seenBssids());
    setSecurity(setting->security());
    setHidden(setting->hidden());
}

NetworkManager::Settings::WirelessSetting::~WirelessSetting()
{
    delete d_ptr;
}

QString NetworkManager::Settings::WirelessSetting::name() const
{
    Q_D(const WirelessSetting);

    return d->name;
}

void NetworkManager::Settings::WirelessSetting::setSsid(const QByteArray& ssid)
{
    Q_D(WirelessSetting);

    d->ssid = ssid;
}

QByteArray NetworkManager::Settings::WirelessSetting::ssid() const
{
    Q_D(const WirelessSetting);

    return d->ssid;
}

void NetworkManager::Settings::WirelessSetting::setMode(NetworkManager::Settings::WirelessSetting::NetworkMode mode)
{
    Q_D(WirelessSetting);

    d->mode = mode;
}

NetworkManager::Settings::WirelessSetting::NetworkMode NetworkManager::Settings::WirelessSetting::mode() const
{
    Q_D(const WirelessSetting);

    return d->mode;
}

void NetworkManager::Settings::WirelessSetting::setBand(NetworkManager::Settings::WirelessSetting::FrequencyBand band)
{
    Q_D(WirelessSetting);

    d->band = band;
}

NetworkManager::Settings::WirelessSetting::FrequencyBand NetworkManager::Settings::WirelessSetting::band() const
{
    Q_D(const WirelessSetting);

    return d->band;
}

void NetworkManager::Settings::WirelessSetting::setChannel(quint32 channel)
{
    Q_D(WirelessSetting);

    d->channel = channel;
}

quint32 NetworkManager::Settings::WirelessSetting::channel() const
{
    Q_D(const WirelessSetting);

    return d->channel;
}

void NetworkManager::Settings::WirelessSetting::setBssid(const QByteArray& bssid)
{
    Q_D(WirelessSetting);

    d->bssid = bssid;
}

QByteArray NetworkManager::Settings::WirelessSetting::bssid() const
{
    Q_D(const WirelessSetting);

    return d->bssid;
}

void NetworkManager::Settings::WirelessSetting::setRate(quint32 rate)
{
    Q_D(WirelessSetting);

    d->rate = rate;
}

quint32 NetworkManager::Settings::WirelessSetting::rate() const
{
    Q_D(const WirelessSetting);

    return d->rate;
}

void NetworkManager::Settings::WirelessSetting::setTxPower(quint32 power)
{
    Q_D(WirelessSetting);

    d->txPower = power;
}

quint32 NetworkManager::Settings::WirelessSetting::txPower() const
{
    Q_D(const WirelessSetting);

    return d->txPower;
}

void NetworkManager::Settings::WirelessSetting::setMacAddress(const QByteArray& address)
{
    Q_D(WirelessSetting);

    d->macAddress = address;
}

QByteArray NetworkManager::Settings::WirelessSetting::macAddress() const
{
    Q_D(const WirelessSetting);

    return d->macAddress;
}

void NetworkManager::Settings::WirelessSetting::setClonedMacAddress(const QByteArray& address)
{
    Q_D(WirelessSetting);

    d->clonedMacAddress = address;
}

QByteArray NetworkManager::Settings::WirelessSetting::clonedMacAddress() const
{
    Q_D(const WirelessSetting);

    return d->clonedMacAddress;
}

void NetworkManager::Settings::WirelessSetting::setMacAddressBlacklist(const QStringList& list)
{
    Q_D(WirelessSetting);

    d->macAddressBlacklist = list;
}

QStringList NetworkManager::Settings::WirelessSetting::macAddressBlacklist() const
{
    Q_D(const WirelessSetting);

    return d->macAddressBlacklist;
}

void NetworkManager::Settings::WirelessSetting::setMtu(quint32 mtu)
{
    Q_D(WirelessSetting);

    d->mtu = mtu;
}

quint32 NetworkManager::Settings::WirelessSetting::mtu() const
{
    Q_D(const WirelessSetting);

    return d->mtu;
}

void NetworkManager::Settings::WirelessSetting::setSeenBssids(const QStringList& list)
{
    Q_D(WirelessSetting);

    d->seenBssids = list;
}

QStringList NetworkManager::Settings::WirelessSetting::seenBssids() const
{
    Q_D(const WirelessSetting);

    return d->seenBssids;
}

void NetworkManager::Settings::WirelessSetting::setSecurity(const QString& security)
{
    Q_D(WirelessSetting);

    d->security = security;
}

QString NetworkManager::Settings::WirelessSetting::security() const
{
    Q_D(const WirelessSetting);

    return d->security;
}

void NetworkManager::Settings::WirelessSetting::setHidden(bool hidden)
{
    Q_D(WirelessSetting);

    d->hidden = hidden;
}

bool NetworkManager::Settings::WirelessSetting::hidden() const
{
    Q_D(const WirelessSetting);

    return d->hidden;
}

bool NetworkManager::Settings::WirelessSetting::hasSecrets() const
{
    return false;
}

void NetworkManager::Settings::WirelessSetting::fromMap(const QVariantMap& setting)
{
    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_SSID))) {
        setSsid(setting.value(QLatin1String(NM_SETTING_WIRELESS_SSID)).toByteArray());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_MODE))) {
        QString mode = setting.value(QLatin1String(NM_SETTING_WIRELESS_MODE)).toString();
        if (mode == QLatin1String(NM_SETTING_WIRELESS_MODE_INFRA)) {
            setMode(Infrastructure);
        } else if (mode == QLatin1String(NM_SETTING_WIRELESS_MODE_ADHOC)) {
            setMode(Adhoc);
        } else if (mode == QLatin1String(NM_SETTING_WIRELESS_MODE_AP)) {
            setMode(Ap);
        }
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_BAND))) {
        QString band = setting.value(QLatin1String(NM_SETTING_WIRELESS_BAND)).toString();
        if (band == "a") {
            setBand(A);
        } else if (band == "bg") {
            setBand(Bg);
        }
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_CHANNEL))) {
        setChannel(setting.value(QLatin1String(NM_SETTING_WIRELESS_CHANNEL)).toUInt());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_BSSID))) {
        setBssid(setting.value(QLatin1String(NM_SETTING_WIRELESS_BSSID)).toByteArray());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_RATE))) {
        setRate(setting.value(QLatin1String(NM_SETTING_WIRELESS_RATE)).toUInt());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_TX_POWER))) {
        setTxPower(setting.value(QLatin1String(NM_SETTING_WIRELESS_TX_POWER)).toUInt());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_MAC_ADDRESS))) {
        setMacAddress(setting.value(QLatin1String(NM_SETTING_WIRELESS_MAC_ADDRESS)).toByteArray());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_CLONED_MAC_ADDRESS))) {
        setClonedMacAddress(setting.value(QLatin1String(NM_SETTING_WIRELESS_CLONED_MAC_ADDRESS)).toByteArray());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_MAC_ADDRESS_BLACKLIST))) {
        setMacAddressBlacklist(setting.value(QLatin1String(NM_SETTING_WIRELESS_MAC_ADDRESS_BLACKLIST)).toStringList());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_MTU))) {
        setMtu(setting.value(QLatin1String(NM_SETTING_WIRELESS_MTU)).toUInt());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_SEEN_BSSIDS))) {
        setSeenBssids(setting.value(QLatin1String(NM_SETTING_WIRELESS_SEEN_BSSIDS)).toStringList());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_SEC))) {
        setSecurity(setting.value(QLatin1String(NM_SETTING_WIRELESS_SEC)).toString());
    }

    if (setting.contains(QLatin1String(NM_SETTING_WIRELESS_HIDDEN))) {
        setHidden(setting.value(QLatin1String(NM_SETTING_WIRELESS_HIDDEN)).toBool());
    }
}

QVariantMap NetworkManager::Settings::WirelessSetting::toMap() const
{
    QVariantMap setting;

    if (!ssid().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_SSID), ssid());
    }

    if (mode() == Infrastructure) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_MODE), QLatin1String(NM_SETTING_WIRELESS_MODE_INFRA));
    } else if (mode() == Adhoc) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_MODE), QLatin1String(NM_SETTING_WIRELESS_MODE_ADHOC));
    } else if (mode() == Ap) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_MODE), QLatin1String(NM_SETTING_WIRELESS_MODE_AP));
    }

    if (band() != Automatic) {
        if (band() == A) {
            setting.insert(QLatin1String(NM_SETTING_WIRELESS_BAND), "a");
        } else if (band() ==  Bg) {
            setting.insert(QLatin1String(NM_SETTING_WIRELESS_BAND), "bg");
        }
    }

    if (channel()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_CHANNEL), channel());
    }

    if (!bssid().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_BSSID), bssid());
    }

    if (rate()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_RATE), rate());
    }

    if (txPower()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_TX_POWER), txPower());
    }

    if (!macAddress().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_MAC_ADDRESS), macAddress());
    }

    if (!clonedMacAddress().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_CLONED_MAC_ADDRESS), clonedMacAddress());
    }

    if (!macAddressBlacklist().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_MAC_ADDRESS_BLACKLIST), macAddressBlacklist());
    }

    if (mtu()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_MTU), mtu());
    }

    if (!seenBssids().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_SEEN_BSSIDS), seenBssids());
    }

    if (!security().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_SEC), security());
    }

    if (hidden()) {
        setting.insert(QLatin1String(NM_SETTING_WIRELESS_HIDDEN), hidden());
    }

    return setting;
}


void NetworkManager::Settings::WirelessSetting::printSetting()
{
    NetworkManager::Settings::Setting::printSetting();

    qDebug() << NM_SETTING_WIRELESS_SSID << ": " << ssid();
    qDebug() << NM_SETTING_WIRELESS_MODE << ": " << mode();
    qDebug() << NM_SETTING_WIRELESS_BAND << ": " << band();
    qDebug() << NM_SETTING_WIRELESS_CHANNEL << ": " << channel();
    qDebug() << NM_SETTING_WIRELESS_BSSID << ": " << bssid();
    qDebug() << NM_SETTING_WIRELESS_RATE << ": " << rate();
    qDebug() << NM_SETTING_WIRELESS_TX_POWER << ": " << txPower();
    qDebug() << NM_SETTING_WIRELESS_MAC_ADDRESS << ": " << macAddress();
    qDebug() << NM_SETTING_WIRELESS_CLONED_MAC_ADDRESS << ": " << clonedMacAddress();
    qDebug() << NM_SETTING_WIRELESS_MAC_ADDRESS_BLACKLIST << ": " << macAddressBlacklist();
    qDebug() << NM_SETTING_WIRELESS_MTU << ": " << mtu();
    qDebug() << NM_SETTING_WIRELESS_SEEN_BSSIDS << ": " << seenBssids();
    qDebug() << NM_SETTING_WIRELESS_SEC << ": " << security();
    qDebug() << NM_SETTING_WIRELESS_HIDDEN << ": " << hidden();
}
