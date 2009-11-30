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


#ifndef _ABSTRACT_AGENT_H_
#define _ABSTRACT_AGENT_H_

#include <QtDBus>

#include <device.h>

class AbstractAgent : public QObject, protected QDBusContext
{
    Q_OBJECT

public:
    AbstractAgent() { }
    virtual ~AbstractAgent() { }

public Q_SLOTS:

    virtual void authorize(org::bluez::Device&, const QString&) { reject(); }

    virtual void cancel() { }

    virtual void confirmModeChange(const QString&) { reject(); }

    virtual void displayPasskey(const org::bluez::Device&, uint) { }

    virtual void release() { }

    virtual void requestConfirmation(const org::bluez::Device&, uint) { reject(); }

    virtual uint requestPasskey(const org::bluez::Device&) { return 0;}

    virtual QString requestPinCode(const org::bluez::Device&) { return QString();}

    inline void reject() { sendErrorReply("org.bluez.Error.Rejected", "The request was rejected"); }

};

#endif // _ABSTRACT_AGENT_H_
