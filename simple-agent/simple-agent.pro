TEMPLATE = app

TARGET = simple-agent

QT += dbus

SOURCES = manager.cpp \
          adapter.cpp \
          device.cpp \
          agent.cpp \
          simple-agent.cpp \
          main.cpp \

HEADERS = abstractagent.h \
          adapter.h \
          device.h \
          agent.h \
          manager.h \
          simple-agent.h \
