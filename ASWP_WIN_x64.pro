QT      += core gui
QT      += widgets
QT      += serialport
QT      += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11
LIBS += -lws2_32
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    libmodbus/libmodbus-3.1.2/src/modbus-data.c \
    libmodbus/libmodbus-3.1.2/src/modbus-rtu.c \
    libmodbus/libmodbus-3.1.2/src/modbus-tcp.c \
    libmodbus/libmodbus-3.1.2/src/modbus.c \
    servicewindow.cpp \
    slavemodbus.cpp \
    thread.cpp

HEADERS += \
    main.h \
    mainwindow.h \
    libmodbus/libmodbus-3.1.2/src/modbus-private.h \
    libmodbus/libmodbus-3.1.2/src/modbus-rtu-private.h \
    libmodbus/libmodbus-3.1.2/src/modbus-rtu.h \
    libmodbus/libmodbus-3.1.2/src/modbus-tcp-private.h \
    libmodbus/libmodbus-3.1.2/src/modbus-tcp.h \
    libmodbus/libmodbus-3.1.2/src/modbus-version.h \
    libmodbus/libmodbus-3.1.2/src/modbus-version.h.in \
    libmodbus/libmodbus-3.1.2/src/modbus.h \
    servicewindow.h \
    slavemodbus.h \
    thread.h

FORMS += \
    mainwindow.ui \
    servicewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win64:CONFIG(release, debug|release): LIBS += -L$$PWD/libmodbus/win_x86_64/ -llibmodbus.dll
else:win64:CONFIG(debug, debug|release): LIBS += -L$$PWD/libmodbus/win_x86_64/ -llibmodbus.dll
else:unix: LIBS += -L$$PWD/libmodbus/win_x86_64/ -llibmodbus.dll
win64: RC_ICONS = $$PWD/deg-icon.ico
INCLUDEPATH += $$PWD/libmodbus/libmodbus-3.1.2/src
DEPENDPATH += $$PWD/libmodbus/libmodbus-3.1.2/src

DISTFILES += \
    deg.png \
    sounds/BOLNOY.wav \
    sounds/BVR.wav \
    sounds/DVERI.wav \
    sounds/GRUZ.wav \
    sounds/LUDI.wav \
    sounds/LUDIREGIME.wav \
    sounds/LYADI.wav \
    sounds/NEGABARIT.wav \
    sounds/PRIHOD.wav \
    sounds/REVIZ.wav \
    sounds/STOP.wav \
    sounds/TVERH.wav \
    sounds/TVNIZ.wav \
    sounds/VERH.wav \
    sounds/VNIZ.wav
