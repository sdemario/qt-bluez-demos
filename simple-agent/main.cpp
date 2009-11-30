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


#include <QCoreApplication>
#include <QDebug>
#include <QtDBus>

#include "manager.h"
#include "adapter.h"
#include "simple-agent.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QStringList args = app.arguments();

    if (args.length() < 3) {
        qWarning() << "Usage:" << args.at(0) << " <device address> <passkey>";
        return 0;
    }

    org::bluez::Manager manager(BLUEZ_SERVICE_NAME,
                                BLUEZ_MANAGER_PATH, QDBusConnection::systemBus());

    QDBusPendingReply<QDBusObjectPath> dpath = manager.DefaultAdapter();
    dpath.waitForFinished();
    if (!dpath.isValid()) {
        qCritical() << "Unable to find default Bluetooth adapter";
        return -1;
    }

    QDBusObjectPath adapterPath = dpath.value();

    org::bluez::Adapter adapter(BLUEZ_SERVICE_NAME,
                                adapterPath.path(), QDBusConnection::systemBus());
    if (!adapter.isValid()) {
        qCritical() << "Can't get valid adapter object reference!";
        return -1;
    }

    QDBusPendingReply<QDBusObjectPath> device = adapter.FindDevice(args.at(1));

    device.waitForFinished();
    /* Suppose the user wants to re-pair the device if the device is already known */
    if (device.isValid()) {
        QDBusPendingReply<> reply = adapter.RemoveDevice(device.value());
        reply.waitForFinished();
    }

    SimpleAgent agent(args.at(2).toInt());

    QDBusPendingCall async = adapter.CreatePairedDevice(args.at(1),
                                                        QDBusObjectPath(PAIRING_AGENT_PATH), "");
    QDBusPendingCallWatcher watcher(async);
    QObject::connect(&watcher, SIGNAL(finished(QDBusPendingCallWatcher*)), &agent,
                     SLOT(deviceCreated(QDBusPendingCallWatcher*)));

    return app.exec();
}
