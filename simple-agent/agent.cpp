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


#include <QtDBus>

#include "device.h"
#include "abstractagent.h"
#include "agent.h"


AgentAdaptor::AgentAdaptor(AbstractAgent *parent) :
    QDBusAbstractAdaptor(parent), agent(parent)
{

}

AgentAdaptor::~AgentAdaptor()
{

}

void AgentAdaptor::Authorize(const QDBusObjectPath &deviceObject, const QString &uuid)
{
    if (!agent) {
        return;
    }

    org::bluez::Device device(BLUEZ_SERVICE_NAME, deviceObject.path(), QDBusConnection::systemBus());

    agent->authorize(device, uuid);
}

void AgentAdaptor::Cancel()
{
    if (!agent) {
        return;
    }

    agent->cancel();
}

void AgentAdaptor::ConfirmModeChange(const QString &mode)
{
    if (!agent) {
        return;
    }

    agent->confirmModeChange(mode);
}

void AgentAdaptor::DisplayPasskey(const QDBusObjectPath &deviceObject, uint passkey)
{
    if (!agent) {
        return;
    }

    const org::bluez::Device device(BLUEZ_SERVICE_NAME, deviceObject.path(), QDBusConnection::systemBus());

    agent->displayPasskey(device, passkey);
}

void AgentAdaptor::Release()
{
    if (!agent) {
        return;
    }

    agent->release();
}

void AgentAdaptor::RequestConfirmation(const QDBusObjectPath &deviceObject, uint passkey)
{
    if (!agent) {
        return;
    }

    const org::bluez::Device device(BLUEZ_SERVICE_NAME, deviceObject.path(), QDBusConnection::systemBus());

    agent->requestConfirmation(device, passkey);
}

uint AgentAdaptor::RequestPasskey(const QDBusObjectPath &deviceObject)
{
    if (!agent) {
        return 0;
    }

    const org::bluez::Device device(BLUEZ_SERVICE_NAME, deviceObject.path(), QDBusConnection::systemBus());

    return agent->requestPasskey(device);
}

QString AgentAdaptor::RequestPinCode(const QDBusObjectPath &deviceObject)
{
    if (!agent) {
        return QString();
    }

    const org::bluez::Device device(BLUEZ_SERVICE_NAME, deviceObject.path(), QDBusConnection::systemBus());

    return agent->requestPinCode(device);
}
