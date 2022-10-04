#ifndef SLAVEMODBUS_H
#define SLAVEMODBUS_H
#include "thread.h"
#include <modbus-private.h>
#include <modbus-tcp.h>
#include <modbus-tcp-private.h>
#include <modbus-rtu.h>
#include <modbus-rtu-private.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <QThread>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
class slavemodbus : public QThread
{
     Q_OBJECT

public:
    slavemodbus(QObject * parent = 0 ) : QThread(parent)
    {
        moveToThread(this);
       }
    ~slavemodbus();
virtual void run();

public slots:
  // void plc_out(PLC par);
private:
   int rc;
   int sc;
   modbus_t *ctx;
   modbus_mapping_t *mb_mapping;
   uint8_t query[MODBUS_RTU_MAX_ADU_LENGTH];
};

#endif // SLAVEMODBUS_H
