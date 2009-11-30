/*
 * Qt BlueZ demos - Using BlueZ through Qt
 *
 * Copyright(C) 2009 - Instituto Nokia de Tecnologia
 *
 * This file is part of Qt BlueZ demos.
 *
 * Qt BlueZ demos is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Qt BlueZ demos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Qt BlueZ demos.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _AGENT_H_
#define _AGENT_H_

#include <QtCore/QObject>
#include <QtDBus/QtDBus>

class AbstractAgent;

class AgentAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.bluez.Agent")

public:
    AgentAdaptor(AbstractAgent *parent);
    virtual ~AgentAdaptor();

public slots:
    void Authorize(const QDBusObjectPath &device, const QString &uuid);
    void Cancel();
    void ConfirmModeChange(const QString &mode);
    void DisplayPasskey(const QDBusObjectPath &device, uint passkey);
    void Release();
    void RequestConfirmation(const QDBusObjectPath &device, uint passkey);
    uint RequestPasskey(const QDBusObjectPath &device);
    QString RequestPinCode(const QDBusObjectPath &device);

private:
    AbstractAgent *agent;
};

#endif // _AGENT_H_
