#ifndef THREAD_H
#define THREAD_H

#include "main.h"
#include "mainwindow.h"
#include <QThread>
#include <QDebug>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QString>
#include <qstandardpaths.h>
#include <modbus.h>
#include <QSound>
#include <modbus-private.h>
#include <modbus-tcp.h>
#include <modbus-tcp-private.h>
#include <modbus-rtu.h>
#include <modbus-rtu-private.h>

class thread : public QThread
{
     Q_OBJECT
public:
    thread(QObject * parent = 0 ) : QThread(parent)
    {
        moveToThread(this);
       }
    ~thread();
virtual void run();

private:
    modbus_t *ctx;
    uint16_t tab_reg[26];
    QTimer *tmrMB;
    QTimer *tmrSer;
    device_parametrs device_parametrs_readed;
    bvv_DI DI_readed;
    bvv_DO DO_readed;
    QString workmode;
    QString horizon;
    QString deny0;
    QString deny175;
    QString deny265;
    QString deny0l175l265;
    QString worksignal;

    QSerialPort serial;
    bool x;

    int rc;
    int i;   

signals:
    void send(int);
    void device_param(device_parametrs par);
    void bvv_in(bvv_DI par1);
    void bvv_out(bvv_DO par2);
    void send_log();
    void send_log_2();
//---------------------------------------------------------------------------------------------------------------------------------------------------------
    void call_ser();
    void scroll();
//---------------------------------------------------------------------------------------------------------------------------------------------------------
public slots:
    void dis_ser();
    void start_tmr_ser();
    void m_Timeout();
    void write_log();
    void write_log_2();
    void stoptmr();
};


#endif // THREAD_H
