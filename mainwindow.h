#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "thread.h"
#include "main.h"
#include <QThread>
#include <QDebug>
#include <modbus.h>
#include <modbus-private.h>
#include <modbus-tcp.h>
#include <modbus-tcp-private.h>
#include <modbus-rtu.h>
#include <modbus-rtu-private.h>
#include <stdint.h>
#include <qmath.h>
#include <QtMath>
#include <QTime>
#include <QSound>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QListView>
#include <QPalette>
#include <QScrollBar>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QCloseEvent>
#include <QStandardItemModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
       QTimer *tmr; //Адресная переменная таймера

       QString cwData;
       QStandardItemModel *csvModel;

       device_parametrs    device_parm;
       //-------------------
       QPalette clr_pink;
       QPalette clr_red;
       QPalette clr_red_wind;
       QPalette clr_green;
       QPalette clr_green_notsogreen;
       QPalette clr_banana;
       QPalette clr_blue;
       QPalette clr_blue_notsoblue;
       QPalette clr_white;
       QPalette clr_white_wind;
       QPalette clr_black;
       QPalette clr_gray;
       //-------------------
      // QSerialPort serial;
       bool x;


signals:
      void openservice();

private slots:
    void timeout(); //Слот для обновления времени на экране

    void on_pushButton_2_clicked();
    void opened();
    void on_pushButton_clicked();

    void on_calendarWidget_selectionChanged();

public slots:
    void log();
    void scroll();
    void device_param(device_parametrs par);
    void bvv_in(bvv_DI par1);
    void bvv_out(bvv_DO par2);
    void read();

};
#endif // MAINWINDOW_H
