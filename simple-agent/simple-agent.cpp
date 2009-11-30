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
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Qt BlueZ demos.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QCoreApplication>
#include <QDebug>
#include <QtDBus>

#include "agent.h"
#include "simple-agent.h"

SimpleAgent::SimpleAgent(uint passkey):
    m_passkey(passkey)
{
    new AgentAdaptor(this);
    QDBusConnection::systemBus().registerObject(PAIRING_AGENT_PATH, this);
}

SimpleAgent::~SimpleAgent()
{

}

void SimpleAgent::displayPasskey(const org::bluez::Device&, uint passkey)
{
    qDebug() << "Passkey:" << passkey;
}

void SimpleAgent::requestConfirmation(const org::bluez::Device&, uint)
{

}

uint SimpleAgent::requestPasskey(const org::bluez::Device&)
{
    return m_passkey;
}

QString SimpleAgent::requestPinCode(const org::bluez::Device&)
{
    QString pinCode;
    pinCode.sprintf("%.4d", m_passkey);
    return pinCode;
}

void SimpleAgent::release()
{

}

void SimpleAgent::deviceCreated(QDBusPendingCallWatcher *call)
{
    QDBusPendingReply<QDBusObjectPath> reply = *call;

    if (reply.isValid()) {
        qWarning() << "Pairing sucessfull";
    } else {
        QDBusError error = reply.error();
        qWarning() << "Pairing failed:" << error.name() << error.message();
    }

    qApp->quit();
}
