#include "mainwindow.h"
#include "servicewindow.h"
#include "thread.h"
#include "slavemodbus.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    servicewindow s;
    thread th;
    qRegisterMetaType<device_parametrs>("device_parametrs");
    qRegisterMetaType<bvv_DI>("bvv_DI");
    qRegisterMetaType<bvv_DO>("bvv_DO");

    QObject::connect(&th, SIGNAL(send_read()), &w, SLOT(read()));

    QObject::connect(&th, SIGNAL(device_param(device_parametrs)), &w, SLOT(device_param(device_parametrs)));

    QObject::connect(&th, SIGNAL(scroll()),       &w,   SLOT(scroll()));
    QObject::connect(&th, SIGNAL(send_log()),     &w,   SLOT(log()));

    QObject::connect(&w, SIGNAL(openservice()), &s, SLOT(opened()));
    QObject::connect(&s, SIGNAL(openmain()), &w, SLOT(opened()));
    QObject::connect(&th, SIGNAL(bvv_in(bvv_DI)), &w, SLOT(bvv_in(bvv_DI)));
    QObject::connect(&th, SIGNAL(bvv_out(bvv_DO)), &w, SLOT(bvv_out(bvv_DO)));

    QObject::connect(&th, SIGNAL(send(int)), &s, SLOT(get(int)));
    QObject::connect(&th, SIGNAL(bvv_in(bvv_DI)), &s, SLOT(bvv_in(bvv_DI)));
    QObject::connect(&th, SIGNAL(bvv_out(bvv_DO)), &s, SLOT(bvv_out(bvv_DO)));
    QObject::connect(&th, SIGNAL(device_param(device_parametrs)), &s, SLOT(device_param(device_parametrs)));
    QObject::connect(&th, SIGNAL(send_log_2()),     &s,   SLOT(log()));
    QObject::connect(&th, SIGNAL(scroll()),         &s,   SLOT(scroll()));

    w.show();


    w.showFullScreen();
    th.start();

//---------------------------------------------------------------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------------------------------------------------------
    return a.exec();
}
