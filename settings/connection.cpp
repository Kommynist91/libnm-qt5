/*
    Copyright 2012  Jan Grulich <jgrulich@redhat.com>

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


#include "connection.h"
#include "connection_p.h"

#include <nm-setting-connection.h>
#include <nm-setting-wired.h>
#include <nm-setting-wireless.h>
#include <nm-setting-gsm.h>
#include <nm-setting-bluetooth.h>
#include <nm-setting-cdma.h>
#include <nm-setting-pppoe.h>
#include <nm-setting-vpn.h>

#include "802-3-ethernet.h"
#include "802-11-wireless.h"
#include "802-11-wireless-security.h"
#include "bluetooth.h"
#include "bond.h"
#include "gsm.h"
#include "cdma.h"
#include "infiniband.h"
#include "ppp.h"
#include "ipv4.h"
#include "ipv6.h"

#include <QUuid>

NetworkManager::Settings::ConnectionSettingsPrivate::ConnectionSettingsPrivate():
    name(QString("connection")),
    id(QString()),
    uuid(QUuid().toString()),
    type(ConnectionSettings::Wired),
    permissions(QHash<QString,QString>()),
    autoconnect(true),
    timestamp(QDateTime()),
    readOnly(false),
    zone(QString()),
    master(QString()),
    slaveType(QString())
{
}

NetworkManager::Settings::ConnectionSettings::ConnectionType NetworkManager::Settings::ConnectionSettings::typeFromString(const QString & typeString)
{
    ConnectionSettings::ConnectionType type = Wired;

    if (typeString == QLatin1String(NM_SETTING_WIRED_SETTING_NAME)) {
        type = Wired;
    } else if (typeString == QLatin1String(NM_SETTING_WIRELESS_SETTING_NAME)) {
        type = Wireless;
    } else if (typeString == QLatin1String(NM_SETTING_GSM_SETTING_NAME)) {
        type = Gsm;
    } else if (typeString == QLatin1String(NM_SETTING_CDMA_SETTING_NAME)) {
        type = Cdma;
    } else if (typeString == QLatin1String(NM_SETTING_BLUETOOTH_SETTING_NAME)) {
        type = Bluetooth;
    } else if (typeString == QLatin1String(NM_SETTING_VPN_SETTING_NAME)) {
        type = Vpn;
    } else if (typeString == QLatin1String(NM_SETTING_PPPOE_SETTING_NAME)) {
        type = Pppoe;
    }

    return type;
}

QString NetworkManager::Settings::ConnectionSettings::typeAsString(NetworkManager::Settings::ConnectionSettings::ConnectionType type)
{
    QString typeString;

    switch (type) {
        case Wired:
            typeString = QLatin1String("802-3-ethernet");
            break;
        case Wireless:
            typeString = QLatin1String("802-11-wireless");
            break;
        case Gsm:
            typeString = QLatin1String("gsm");
            break;
        case Cdma:
            typeString = QLatin1String("cdma");
            break;
        case Bluetooth:
            typeString = QLatin1String("bluetooth");
            break;
        case Vpn:
            typeString = QLatin1String("vpn");
            break;
        case Pppoe:
            typeString = QLatin1String("pppoe");
            break;
        default:
            break;
    }

    return typeString;
}


NetworkManager::Settings::ConnectionSettings::ConnectionSettings():
    d_ptr(new ConnectionSettingsPrivate())
{ }

NetworkManager::Settings::ConnectionSettings::ConnectionSettings(NetworkManager::Settings::ConnectionSettings::ConnectionType type):
    d_ptr(new ConnectionSettingsPrivate())
{
    setConnectionType(type);
}

NetworkManager::Settings::ConnectionSettings::ConnectionSettings(NetworkManager::Settings::ConnectionSettings* settings):
    d_ptr(new ConnectionSettingsPrivate())
{
    setId(settings->id());
    setUuid(settings->uuid());
    setConnectionType(settings->connectionType());
    setPermissions(settings->permissions());
    setAutoconnect(settings->autoconnect());
    setTimestamp(settings->timestamp());
    setReadOnly(settings->readOnly());
    setZone(settings->zone());
    setMaster(settings->master());
    setSlaveType(settings->slaveType());

    initSettings();
}

NetworkManager::Settings::ConnectionSettings::~ConnectionSettings()
{
    clearSettings();

    delete d_ptr;
}

void NetworkManager::Settings::ConnectionSettings::initSettings()
{
    clearSettings();

    switch(connectionType()) {
        case Adsl:
            //TODO: Implement ADSL setting
            //addSetting(new AdslSetting());
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            break;
        case Bond:
            addSetting(new BondSetting());
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            break;
        case Bluetooth:
            addSetting(new BluetoothSetting());
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            //TODO: check for Bluetooth type
            addSetting(new GsmSetting());
            addSetting(new CdmaSetting());
            addSetting(new PPPSetting());
            //TODO: implement Serial setting
            //addSetting(new SerialSetting());
            break;
        case Cdma:
            addSetting(new CdmaSetting());
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            addSetting(new PPPSetting());
            break;
        case Gsm:
            addSetting(new GsmSetting());
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            addSetting(new PPPSetting());
            break;
        case Infiniband:
            addSetting(new InfinibandSetting());
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
        case OLPCMesh:
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            //TODO: implement OLPCMesh setting
            //addSetting(new OLPCMeshSetting());
        case Pppoe:
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            addSetting(new PPPSetting());
            //TODO: Implement PPPoESetting
            //addSetting(new PppoeSetting());
            addSetting(new WiredSetting());
        case Vlan:
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            //TODO: Implement VLan setting
            //addSetting(new VlanSetting());
        case Vpn:
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            //TODO: Implement VPN setting
            //addSetting(new VpnSetting());
            break;
        case Wimax:
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            //TODO: Implement Wimax setting
            //addSetting(new WimaxSetting());
        case Wired:
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            //TODO: Implement Security8021xSetting
            //addSetting(new Security8021xSetting());
            addSetting(new WiredSetting());
            break;
        case Wireless:
            addSetting(new Ipv4Setting());
            addSetting(new Ipv6Setting());
            //TODO: Implement Security8021xSetting
            //addSetting(new Security8021xSetting());
            addSetting(new WirelessSetting());
            addSetting(new WirelessSecuritySetting());
            break;
	case Unknown:
	    break;
	default:
	    break;
    }
}

void NetworkManager::Settings::ConnectionSettings::fromMap(const QVariantMapMap& map)
{
    QVariantMap connectionSettings = map.value(QLatin1String(NM_SETTING_CONNECTION_SETTING_NAME));

    setId(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_ID)).toString());
    setUuid(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_UUID)).toString());
    setConnectionType(typeFromString(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_TYPE)).toString()));

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_PERMISSIONS))) {
	QStringList permissions = connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_PERMISSIONS)).toStringList();
        foreach (const QString &permission, permissions) {
            QStringList split = permission.split(QLatin1String(":"), QString::KeepEmptyParts);
            addToPermissions(split.at(1),split.at(2));
        }
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT))) {
	setAutoconnect(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT)).toBool());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_TIMESTAMP))) {
	int timestamp = connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_TIMESTAMP)).toInt();
        QDateTime dateTime;
        dateTime.setTime_t(timestamp);
        setTimestamp(dateTime);
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_READ_ONLY))) {
	setReadOnly(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_READ_ONLY)).toBool());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_ZONE))) {
	setZone(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_ZONE)).toString());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_MASTER))) {
        setMaster(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_MASTER)).toString());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_SLAVE_TYPE))) {
	setSlaveType(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_SLAVE_TYPE)).toString());
    }

    foreach (Setting * setting, settings()) {
	if (map.contains(setting->typeAsString(setting->type()))) {
	    setting->fromMap(map.value(setting->typeAsString(setting->type())));
	    setting->setInitialized(true);
	} else {
	    setting->setInitialized(false);
	}
    }
}

QVariantMapMap NetworkManager::Settings::ConnectionSettings::toMap() const
{
    QVariantMapMap result;
    QVariantMap connectionSetting;

    if (!id().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_ID), id());
    }

    if (!uuid().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_UUID), uuid());
    }

    if (connectionType()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_TYPE), typeAsString(connectionType()));
    }

    if (!permissions().isEmpty()) {
        QStringList perm;
        foreach (const QString & key, permissions().keys()) {
            QString tmp = "user:" + key + ":" + permissions().value(key);
            perm << tmp;
        }

        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_PERMISSIONS), perm);
    }

    if (!autoconnect()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT), autoconnect());
    }

    if (timestamp().isValid()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_TIMESTAMP), timestamp().toTime_t());
    }

    if (readOnly()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_READ_ONLY), readOnly());
    }

    if (!zone().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_ZONE), zone());
    }

    if (!master().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_MASTER), master());
    }

    if (!slaveType().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_SLAVE_TYPE), slaveType());
    }

    result.insert(QLatin1String(NM_SETTING_CONNECTION_SETTING_NAME), connectionSetting);

    foreach (Setting * setting, settings()) {
        QVariantMap map = setting->toMap();
        result.insert(setting->name(), map);
    }
    return result;
}

QString NetworkManager::Settings::ConnectionSettings::name() const
{
    Q_D(const ConnectionSettings);

    return d->name;
}

void NetworkManager::Settings::ConnectionSettings::setId(const QString& id)
{
    Q_D(ConnectionSettings);

    d->id = id;
}

QString NetworkManager::Settings::ConnectionSettings::id() const
{
    Q_D(const ConnectionSettings);

    return d->id;
}

void NetworkManager::Settings::ConnectionSettings::setUuid(const QString& uuid)
{
    Q_D(ConnectionSettings);

    d->uuid = uuid;
}

QString NetworkManager::Settings::ConnectionSettings::uuid() const
{
    Q_D(const ConnectionSettings);

    return d->uuid;
}

void NetworkManager::Settings::ConnectionSettings::setConnectionType(NetworkManager::Settings::ConnectionSettings::ConnectionType type)
{
    Q_D(ConnectionSettings);

    d->type = type;

    initSettings();
}

NetworkManager::Settings::ConnectionSettings::ConnectionType NetworkManager::Settings::ConnectionSettings::connectionType() const
{
    Q_D(const ConnectionSettings);

    return d->type;
}

void NetworkManager::Settings::ConnectionSettings::addToPermissions(const QString& user, const QString& type)
{
    Q_D(ConnectionSettings);

    d->permissions.insert(user, type);
}

void NetworkManager::Settings::ConnectionSettings::setPermissions(const QHash< QString, QString >& perm)
{
    Q_D(ConnectionSettings);

    d->permissions = perm;
}

QHash< QString, QString > NetworkManager::Settings::ConnectionSettings::permissions() const
{
    Q_D(const ConnectionSettings);

    return d->permissions;
}

void NetworkManager::Settings::ConnectionSettings::setAutoconnect(bool autoconnect)
{
    Q_D(ConnectionSettings);

    d->autoconnect = autoconnect;
}

bool NetworkManager::Settings::ConnectionSettings::autoconnect() const
{
    Q_D(const ConnectionSettings);

    return d->autoconnect;
}

void NetworkManager::Settings::ConnectionSettings::setTimestamp(const QDateTime& timestamp)
{
    Q_D(ConnectionSettings);

    d->timestamp = timestamp;
}

QDateTime NetworkManager::Settings::ConnectionSettings::timestamp() const
{
    Q_D(const ConnectionSettings);

    return d->timestamp;
}

void NetworkManager::Settings::ConnectionSettings::setReadOnly(bool readonly)
{
    Q_D(ConnectionSettings);

    d->readOnly = readonly;
}

bool NetworkManager::Settings::ConnectionSettings::readOnly() const
{
    Q_D(const ConnectionSettings);

    return d->readOnly;
}

void NetworkManager::Settings::ConnectionSettings::setZone(const QString& zone)
{
    Q_D(ConnectionSettings);

    d->zone = zone;
}

QString NetworkManager::Settings::ConnectionSettings::zone() const
{
    Q_D(const ConnectionSettings);

    return d->zone;
}

void NetworkManager::Settings::ConnectionSettings::setMaster(const QString & master)
{
    Q_D(ConnectionSettings);

    d->master = master;
}

QString NetworkManager::Settings::ConnectionSettings::master() const
{
    Q_D(const ConnectionSettings);

    return d->master;
}

void NetworkManager::Settings::ConnectionSettings::setSlaveType(const QString& type)
{
    Q_D(ConnectionSettings);

    d->slaveType = type;
}

QString NetworkManager::Settings::ConnectionSettings::slaveType() const
{
    Q_D(const ConnectionSettings);

    return d->slaveType;
}

NetworkManager::Settings::Setting* NetworkManager::Settings::ConnectionSettings::setting(NetworkManager::Settings::Setting::SettingType type) const
{
    foreach (Setting * setting, settings()) {
        if (setting->type() == type) {
            return setting;
        }
    }

    return 0;
}

QList< NetworkManager::Settings::Setting* > NetworkManager::Settings::ConnectionSettings::settings() const
{
    Q_D(const ConnectionSettings);

    return d->settings;
}

//FOR DEBUG
void NetworkManager::Settings::ConnectionSettings::printSetting()
{
    qDebug() << "CONNECTION SETTINGS";
    qDebug() << "===================";

    qDebug() << "NAME - " << name();
    qDebug() << "ID - " << id();
    qDebug() << "UUID - " << uuid();
    qDebug() << "TYPE - " << typeAsString(connectionType());
    qDebug() << "PERMISSIONS - " << permissions();
    qDebug() << "AUTOCONNECT - " << autoconnect();
    qDebug() << "TIMESTAMP - " << timestamp().toTime_t();
    qDebug() << "READONLY - " << readOnly();
    qDebug() << "MASTER - " << master();
    qDebug() << "SLAVE TYPE - " << slaveType();
    qDebug() << "===================";
    foreach (Setting * setting, settings()) {
	qDebug() << setting->typeAsString(setting->type()).toUpper() << " SETTINGS";
	qDebug() << "---------------------------";
	setting->printSetting();
	qDebug() << "\n";
    }
}

void NetworkManager::Settings::ConnectionSettings::addSetting(NetworkManager::Settings::Setting* setting)
{
    Q_D(ConnectionSettings);

    d->settings.push_back(setting);
}

void NetworkManager::Settings::ConnectionSettings::clearSettings()
{
    Q_D(ConnectionSettings);

    while (!d->settings.isEmpty()) {
        delete d->settings.takeFirst();
    }

    d->settings.clear();
}