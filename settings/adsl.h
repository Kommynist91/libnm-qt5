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

#ifndef NMQT_SETTINGS_ADSLSETTING_H
#define NMQT_SETTINGS_ADSLSETTING_H

#include "../QtNetworkManager-export.h"
#include "generic-types.h"
#include "setting.h"

#include <QtCore/QString>

namespace NetworkManager
{
namespace Settings
{
class AdslSettingPrivate;

class NMQT_EXPORT AdslSetting : public Setting
{
    Q_DECLARE_PRIVATE(AdslSetting)
public:
    enum Protocol {UnknownProtocol = 0, Pppoa, Pppoe, Ipoatm};
    enum Encapsulation {UnknownEncapsulation = 0, Vcmux, Llc};

    AdslSetting();
    AdslSetting(AdslSetting *);
    ~AdslSetting();

    QString name() const;

    void setUsername(const QString & username);
    QString username() const;

    void setPassword(const QString & password);
    QString password() const;

    void setPasswordFlags(SecretFlagType flags);
    SecretFlagType passwordFlags() const;

    void setProtocol(Protocol protocol);
    Protocol protocol() const;

    void setEncapsulation(Encapsulation encapsulation);
    Encapsulation encapsulation() const;

    void setVpi(quint32 vpi);
    quint32 vpi() const;

    void setVci(quint32 vci);
    quint32 vci() const;

    QStringList needSecrets(bool requestNew = false) const;

    void fromMap(const QVariantMap & setting);

    QVariantMap toMap() const;

    //FOR DEBUG
    void printSetting();

private:
    AdslSettingPrivate * d_ptr;
};
}
}

#endif // NMQT_SETTINGS_ADSLSETTING_H
