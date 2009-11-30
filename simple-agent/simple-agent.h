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


#ifndef _SIMPLE_AGENT_H_
#define _SIMPLE_AGENT_H_

#include "abstractagent.h"
#include "device.h"

class SimpleAgent: public AbstractAgent
{
    Q_OBJECT

public:
    SimpleAgent(uint passkey);
    virtual ~SimpleAgent();

public slots:
    void displayPasskey(const org::bluez::Device &device, uint passkey);

    void requestConfirmation(const org::bluez::Device &device, uint passkey);

    uint requestPasskey(const org::bluez::Device &device);

    QString requestPinCode(const org::bluez::Device &device);

    void release();

public:
    void pair(const QString &address);

private slots:
    void deviceCreated(QDBusPendingCallWatcher *call);

private:
    uint m_passkey;
};

#endif // _SIMPLE_AGENT_H_
