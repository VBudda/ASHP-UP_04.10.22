#ifndef SERVICEWINDOW_H
#define SERVICEWINDOW_H
#include "main.h"

#include <QMainWindow>
#include <QUrl>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <QThread>
#include <QDebug>
#include <QDate>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QCalendarWidget>
#include <QTableWidgetItem>
#include <QTextBrowser>
#include <QTableWidget>
#include <QTextStream>
#include <QMessageBox>
#include <QMainWindow>
#include <QProcess>
#include <QDir>

namespace Ui {
class servicewindow;
}

class servicewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit servicewindow(QWidget *parent = nullptr);
    ~servicewindow();

private:
    QString cwData;
    QStandardItemModel *csvModel;
    Ui::servicewindow *ui;
    QPalette clr_banana;
    QPalette clr_green;
    QPalette clr_white;
    QPalette clr_red;
    bvv_DI bvv_in_readed;
    bvv_DO bvv_out_readed;

    device_parametrs    device_parm;

    QTimer *tmrS;
public slots:
    void bvv_in(bvv_DI par1);
    void bvv_out(bvv_DO par2);
    void device_param(device_parametrs par);
    void get(int rc);
    void log();
    void scroll();
signals:
    void openmain();
private slots:
     void timeout(); //Слот для обновления времени на экране
     void opened();
     void on_pushButton_clicked();
     void on_pushButton_2_clicked();
     void on_pushButton_3_clicked();
     void on_pushButton_5_clicked();
     void on_pushButton_6_clicked();
     void on_pushButton_4_clicked();
     void on_pushButton_7_clicked();
     void on_pushButton_8_clicked();
     void on_pushButton_9_clicked();
     void on_calendarWidget_selectionChanged();
};

#endif // SERVICEWINDOW_H
