#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/DEG/index.png");
    ui->Logo_label->setPixmap(pix);

    clr_pink.setColor(QPalette::Base,QColor(200,0,200));
    clr_red.setColor(QPalette::Base,Qt::red);
    clr_red_wind.setColor(QPalette::Window,Qt::red);
    clr_white.setColor(QPalette::Base,Qt::white);
    clr_white_wind.setColor(QPalette::Window,Qt::white);
    clr_green.setColor(QPalette::Base,Qt::green);
    clr_green_notsogreen.setColor(QPalette::Base,QColor(0,250,150));
    clr_blue.setColor(QPalette::Base,QColor(0,100,250));
    clr_blue_notsoblue.setColor(QPalette::Base,QColor(0,150,250));
    clr_black.setColor(QPalette::Base,QColor(0,0,0));
    clr_banana.setColor(QPalette::Base,Qt::yellow);
    clr_gray.setColor(QPalette::Base,Qt::gray);

    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(4);
    csvModel->setHorizontalHeaderLabels(QStringList() << "ВРЕМЯ" << "РЕЖИМ" << "ГОР." << "КОМАНДЫ" << "БЛОКИРОВКИ");
    ui->tableView->setModel(csvModel); // Устанавливаем модель в таблицу
    ui->tableView->setColumnWidth(0,50);
    ui->tableView->setColumnWidth(1,70);
    ui->tableView->setColumnWidth(2,30);
    ui->tableView->setColumnWidth(3,55);
    ui->tableView->setColumnWidth(4,130);
     ui->tableView->setColumnWidth(5,0);
    x = false;

    tmr = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    tmr->setInterval(1000); // Задаем интервал таймера
    connect(tmr, SIGNAL(timeout()), this, SLOT(timeout())); // Подключаем сигнал таймера к нашему слоту
    tmr->start(); // Запускаем таймер

 /*  QSerialPort serial;
      serial.setPortName("COM2");
      serial.setBaudRate(QSerialPort::Baud1200);
      serial.setDataBits(QSerialPort::Data8);
      serial.setParity(QSerialPort::NoParity);
      serial.setStopBits(QSerialPort::OneStop);
      serial.setFlowControl(QSerialPort::NoFlowControl);
      serial.open(QIODevice::ReadWrite);  */
}

MainWindow::~MainWindow()
{
    delete tmr;
    delete ui;
}

void MainWindow::timeout(){
    ui->time_label->setText(QTime::currentTime().toString());
    QDate now = QDate::currentDate();
    if (QTime::currentTime().secsTo(QTime(00,00,01)) == 0)
    {
        ui->calendarWidget->setSelectedDate(now);
    }

}

void MainWindow::log()
{
    QDate now = QDate::currentDate();
    ui->calendarWidget->selectedDate() = QDate::currentDate();
    if (ui->calendarWidget->selectedDate() == now){

    QDate yearnow = QDate::currentDate();
    QString yearstamp = yearnow.toString(QLatin1String("yyyy"));

    QString timestamp = now.toString(QLatin1String("dd.MM.yy"));
    QString filename = QString::fromLatin1("C:/DEG/log_directory/%1/%2.csv").arg(yearstamp).arg(timestamp);
    QFile file(filename);
 file.close();
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)  )
      {
         QTextStream filename(&file);

         csvModel->clear();

         while (!filename.atEnd())
        {
            csvModel->setHorizontalHeaderLabels(QStringList() << "ВРЕМЯ" << "РЕЖИМ" << "ГОР." << "КОМАНДЫ" << "БЛОКИРОВКИ");
             ui->tableView->setModel(csvModel); // Устанавливаем модель в таблицу
             ui->tableView->setColumnWidth(0,50);
             ui->tableView->setColumnWidth(1,70);
             ui->tableView->setColumnWidth(2,30);
             ui->tableView->setColumnWidth(3,55);
             ui->tableView->setColumnWidth(4,130);
             ui->tableView->setColumnWidth(5,0);
            QString line = filename.readLine();
            // Добавляем в модель по строке с элементами
            QList<QStandardItem *> standardItemsList;

            for (QString item : line.split(";"))
            {
                standardItemsList.append(new QStandardItem(item));
            }
            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
        }
           file.close();
     }

    }
}
void MainWindow::scroll()
{
     QScrollBar *sb = ui->tableView->verticalScrollBar();
     sb->setStyleSheet(QString::fromUtf8("QScrollBar:vertical {"
                                         "    border: 1px solid #999999;"
                                         "    background:white;"
                                         "    width:10px;    "
                                         "    margin: 0px 0px 0px 0px;"
                                         "}"
                                         "QScrollBar::handle:vertical {"
                                         "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                         "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
                                         "    min-height: 0px;"
                                         "}"
                                         "QScrollBar::add-line:vertical {"
                                         "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                         "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
                                         "    height: 0px;"
                                         "    subcontrol-position: bottom;"
                                         "    subcontrol-origin: margin;"
                                         "}"
                                         "QScrollBar::sub-line:vertical {"
                                         "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                         "    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
                                         "    height: 0 px;"
                                         "    subcontrol-position: top;"
                                         "    subcontrol-origin: margin;"
                                         "}"
                                         ));
     sb->setMaximum(99999);
     sb->setValue(99999);
}

void MainWindow::device_param(device_parametrs par)
{
//---------WORK MODE---------------------
    if (par.work_mode == 0 ){
        ui->label_MODE->setText("РЕЖИМ - ЛЮДИ");
   } else if (par.work_mode == 1){
        ui->label_MODE->setText("РЕЖИМ - ГРУЗ");
   } else if (par.work_mode == 2){
        ui->label_MODE->setText("РЕЖИМ - НЕГАБАРИТ");    
   } else if (par.work_mode == 3){
        ui->label_MODE->setText("РЕЖИМ - РЕВИЗИЯ");}
//---------WORK SIGNAL-------------------
    if (par.work_signal == 0){
        ui->label_SIGNAL_2->setText("СТОП");       
        ui->listView_SIGNAL->setPalette(clr_red);
    } else if (par.work_signal == 1){
        ui->label_SIGNAL_2->setText("ВЕРХ");
        ui->listView_SIGNAL->setPalette(clr_green);
    } else if (par.work_signal == 2){
        ui->label_SIGNAL_2->setText("Т.ВЕРХ");
        ui->listView_SIGNAL->setPalette(clr_green_notsogreen);
    } else if (par.work_signal == 3){
        ui->label_SIGNAL_2->setText("ВНИЗ");
        ui->listView_SIGNAL->setPalette(clr_green);
    } else if (par.work_signal == 4){
        ui->label_SIGNAL_2->setText("Т.ВНИЗ");
        ui->listView_SIGNAL->setPalette(clr_green_notsogreen);
    } else if (par.work_signal == 5){
        ui->label_SIGNAL_2->setText("ЛЮДИ");
        ui->listView_SIGNAL->setPalette(clr_blue);
    } else if (par.work_signal == 6){
        ui->label_SIGNAL_2->setText("БВР");
        ui->listView_SIGNAL->setPalette(clr_blue);
    } else if (par.work_signal == 7){
        ui->label_SIGNAL_2->setText("БОЛЬНОЙ");
        ui->listView_SIGNAL->setPalette(clr_blue);}
//---------WORK HORIZON------------------
        if (par.work_horizon == 0){
         ui->label_MODE_2->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
         ui->label_ALARM_PLACE->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
         ui->label_ALARM_PLACE_7->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
         ui->label_ALARM_PLACE_2->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
         ui->label_ALARM_PLACE_8->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
         ui->label_MODE_3->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
         ui->label_ALARM_PLACE_3->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
         ui->label_ALARM_PLACE_4->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
         ui->label_MODE_4->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
         ui->label_ALARM_PLACE_5->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
         ui->label_ALARM_PLACE_6->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));

         ui->listView_horizon_0->setPalette(clr_banana);
         ui->listView_horizon_175->setPalette(clr_black);
         ui->listView_horizon_265->setPalette(clr_black);

        } else if (par.work_horizon == 1){
            ui->label_MODE_2->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE_7->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE_2->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE_8->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_MODE_3->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
            ui->label_ALARM_PLACE_3->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
            ui->label_ALARM_PLACE_4->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
            ui->label_MODE_4->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE_5->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE_6->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));

             ui->listView_horizon_0->setPalette(clr_black);
             ui->listView_horizon_175->setPalette(clr_banana);
             ui->listView_horizon_265->setPalette(clr_black);
        } else if (par.work_horizon == 2){
            ui->label_MODE_2->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE_7->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE_2->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE_8->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_MODE_3->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE_3->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_ALARM_PLACE_4->setStyleSheet(QStringLiteral("QLabel{color: rgb(250, 250, 250);}"));
            ui->label_MODE_4->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
            ui->label_ALARM_PLACE_5->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
            ui->label_ALARM_PLACE_6->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
            ui->listView_horizon_0->setPalette(clr_black);
            ui->listView_horizon_175->setPalette(clr_black);
            ui->listView_horizon_265->setPalette(clr_banana);
       }
//---------KLET LEFT------------------
        if (par.denied_horizon_0 & (1 << 0)){
         ui->listView_DOOR_LEFT1->setPalette(clr_blue_notsoblue);}
         else {ui->listView_DOOR_LEFT1->setPalette(clr_black);}

        if (par.denied_horizon_175 & (1 << 0)){
         ui->listView_DOOR_LEFT2->setPalette(clr_blue_notsoblue);}
         else {ui->listView_DOOR_LEFT2->setPalette(clr_black);}

        if (par.denied_horizon_265 & (1 << 0)){
         ui->listView_DOOR_LEFT3->setPalette(clr_blue_notsoblue);}
         else {ui->listView_DOOR_LEFT3->setPalette(clr_black);}
//---------KLET RIGHT------------------
        if (par.denied_horizon_0 & (1 << 7)){
         ui->listView_DOOR_RIGHT1->setPalette(clr_blue_notsoblue);}
         else {ui->listView_DOOR_RIGHT1->setPalette(clr_black);}

        if (par.denied_horizon_175 & (1 << 2)){
         ui->listView_DOOR_RIGHT2->setPalette(clr_blue_notsoblue);}
         else {ui->listView_DOOR_RIGHT2->setPalette(clr_black);}

        if (par.denied_horizon_265 & (1 << 4)){
         ui->listView_DOOR_RIGHT3->setPalette(clr_blue_notsoblue);}
         else {ui->listView_DOOR_RIGHT3->setPalette(clr_black);}
//---------CONNECTION WITH BVV---------------
        /*if (par.connection_with_BVV & (1 << 0)){
            ui->listView_258->setPalette(clr_banana);
        } else {ui->listView_258->setPalette(clr_red); }
        if (par.connection_with_BVV & (1 << 1)){
            ui->listView_259->setPalette(clr_banana);
        } else {ui->listView_259->setPalette(clr_red); }
        if (par.connection_with_BVV & (1 << 2)){
            ui->listView_261->setPalette(clr_banana);
        } else {ui->listView_261->setPalette(clr_red); }
        if (par.connection_with_BVV & (1 << 3)){
            ui->listView_260->setPalette(clr_banana);
        } else {ui->listView_260->setPalette(clr_red); }
        if (par.connection_with_BVV & (1 << 4)){
            ui->listView_265->setPalette(clr_banana);
        } else {ui->listView_265->setPalette(clr_red); }
        if (par.connection_with_BVV & (1 << 5)){
            ui->listView_264->setPalette(clr_banana);
        } else {ui->listView_264->setPalette(clr_red); }
        if (par.connection_with_BVV & (1 << 6)){
            ui->listView_263->setPalette(clr_banana);
        } else {ui->listView_263->setPalette(clr_red); }
        if (par.connection_with_BVV & (1 << 7)){
            ui->listView_262->setPalette(clr_banana);
        } else {ui->listView_262->setPalette(clr_red); } */
//---------DENIED HORIZON 0-------------------
        // двери
        if (par.denied_horizon_0 & (1 << 1)){
            ui->listView->setPalette(clr_red);
        } else {ui->listView->setPalette(clr_white);}
        if (par.denied_horizon_0 & (1 << 2)){
            ui->listView_2->setPalette(clr_red);
        } else {ui->listView_2->setPalette(clr_white);}
        if (par.denied_horizon_0 & (1 << 8)){
            ui->listView_7->setPalette(clr_red);
        } else {ui->listView_7->setPalette(clr_white);}
        if (par.denied_horizon_0 & (1 << 9)){
            ui->listView_8->setPalette(clr_red);
        } else {ui->listView_8->setPalette(clr_white);}
        //кулаки
        if (par.denied_horizon_0 & (1 << 3)){
            ui->listView_3->setPalette(clr_green);
        } else {ui->listView_3->setPalette(clr_red);}
        if (par.denied_horizon_0 & (1 << 10)){
            ui->listView_9->setPalette(clr_green);
        } else {ui->listView_9->setPalette(clr_red);}
       // ляды
        if (par.denied_horizon_0 & (1 << 11)){
            ui->listView_4->setPalette(clr_red);
        } else {ui->listView_4->setPalette(clr_black);}
        if (par.denied_horizon_0 & (1 << 4)){
            ui->listView_10->setPalette(clr_red);
        } else {ui->listView_10->setPalette(clr_black);}
        // переподъем
        if (par.denied_horizon_0 & (1 << 5)){
            ui->listView_5->setPalette(clr_banana);
        } else {ui->listView_5->setPalette(clr_black);}
        if (par.denied_horizon_0 & (1 << 13)){
            ui->listView_11->setPalette(clr_banana);
        } else {ui->listView_11->setPalette(clr_black);}
        // переподъем копровой
        if (par.denied_horizon_0 & (1 << 6)){
            ui->listView_6->setPalette(clr_red);
        } else {ui->listView_6->setPalette(clr_black);}
        if (par.denied_horizon_0 & (1 << 14)){
            ui->listView_12->setPalette(clr_red);
        } else {ui->listView_12->setPalette(clr_black);}
//---------DENIED HORIZON 175-------------------
        // двери
        if (par.denied_horizon_175 & (1 << 1)){
            ui->listView_15->setPalette(clr_red);
        } else {ui->listView_15->setPalette(clr_white);}
        if (par.denied_horizon_175 & (1 << 3)){
            ui->listView_14->setPalette(clr_red);
        } else {ui->listView_14->setPalette(clr_white);}
//---------DENIED HORIZON 265-------------------
        // двери
        if (par.denied_horizon_265 & (1 << 1)){
            ui->listView_13->setPalette(clr_red);
        } else {ui->listView_13->setPalette(clr_white);}
        if (par.denied_horizon_265 & (1 << 2)){
            ui->listView_17->setPalette(clr_red);
        } else {ui->listView_17->setPalette(clr_white);}
        if (par.denied_horizon_265 & (1 << 5)){
            ui->listView_16->setPalette(clr_red);
        } else {ui->listView_16->setPalette(clr_white);}
        if (par.denied_horizon_265 & (1 << 6)){
            ui->listView_18->setPalette(clr_red);
        } else {ui->listView_18->setPalette(clr_white);}
       // т. канаты
        if (par.denied_horizon_265 & (1 << 3)){
            ui->listView_19->setPalette(clr_red);
        } else {ui->listView_19->setPalette(clr_black);}
        if (par.denied_horizon_265 & (1 << 7)){
            ui->listView_20->setPalette(clr_red);
        } else {ui->listView_20->setPalette(clr_black);}
}


void MainWindow::bvv_in(bvv_DI par1)
{

   /* if ((par1.bvv_DI_5 & ( 1 << 7)) && (par1.bvv_DI_3 & ( 1 << 7)) && (par1.bvv_DI_7 & ( 1 << 7))) {

             ui->label_ALARM->hide();

             //ui->label_ALARM->setText(" ");
             ui->listView_ALARM->setPalette(clr_black);
    } else { ui->listView_ALARM->setPalette(clr_red);
             ui->label_ALARM->show();

             //ui->label_ALARM->setText("АВАРИЯ!");
    }*/
    if ((par1.bvv_DI_3 & ( 1 << 7)))
    {
            ui->label_ALARM_PLACE->hide();
            ui->label_ALARM_PLACE_7->hide();
    } else {ui->label_ALARM_PLACE->show();
            ui->label_ALARM_PLACE_7->show();}
    if ((par1.bvv_DI_5 & ( 1 << 7)))
    {
            ui->label_ALARM_PLACE_3->hide();
            ui->label_ALARM_PLACE_4->hide();
    } else {ui->label_ALARM_PLACE_3->show();
            ui->label_ALARM_PLACE_4->show();}
    if ((par1.bvv_DI_7 & ( 1 << 7)))
    {
            ui->label_ALARM_PLACE_5->hide();
            ui->label_ALARM_PLACE_6->hide();
    } else {ui->label_ALARM_PLACE_5->show();
            ui->label_ALARM_PLACE_6->show();}
    if ((par1.bvv_DI_9 & ( 1 << 0)))
    {
            ui->label_ALARM_PLACE_2->hide();
            ui->label_ALARM_PLACE_8->hide();
    } else {ui->label_ALARM_PLACE_2->show();
            ui->label_ALARM_PLACE_8->show();}


}
void MainWindow::bvv_out(bvv_DO par2)
{
    if ((par2.bvv_DO_1 & ( 1 << 12))){
          ui->label_ALARM->show();
          ui->listView_ALARM->setPalette(clr_red);
                                     }
    else {ui->label_ALARM->hide();
            ui->listView_ALARM->setPalette(clr_black);
         }
}

void MainWindow::read()
{

}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
    emit openservice();
}
void MainWindow::opened()
{
  this->show();
  showFullScreen();
}

void MainWindow::on_pushButton_clicked()
{   QDir().mkdir("D:/log_directory/");
    QDate yearnow = ui->calendarWidget->selectedDate();
    QString yearstamp = yearnow.toString(QLatin1String("yyyy"));

    QString source = QString::fromLatin1("C:/DEG/log_directory/%1").arg(yearstamp);
    QString targetplace = QString::fromLatin1("D:/log_directory/%1").arg(yearstamp);

    QDir targetDir(targetplace);
           targetDir.cdUp();
           targetDir.mkdir(QFileInfo(targetplace).fileName());
           QDir sourceDir(source);
           QStringList fileNames = sourceDir.entryList(QDir::Dirs | QDir::Files);
           foreach (const QString fileName, fileNames) {
               const QString newsource = source + "/" + fileName;
               const QString newtarget = targetplace + "/"+ fileName;
                     QFile::copy(newsource, newtarget);
                    }       
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    QDate yearnow = ui->calendarWidget->selectedDate();
    QString yearstamp = yearnow.toString(QLatin1String("yyyy"));

       QString timestamp = ui->calendarWidget->selectedDate().toString(QLatin1String("dd.MM.yy"));
       QString filename = QString::fromLatin1("C:/DEG/log_directory/%1/%2.csv").arg(yearstamp).arg(timestamp);
       QFile file(filename);
        file.close();

       if(file.open(QIODevice::ReadOnly | QIODevice::Text))
         {
            QTextStream filename(&file);
             csvModel->clear();

            while (!filename.atEnd())
           {
                csvModel->setHorizontalHeaderLabels(QStringList() << "ВРЕМЯ" << "РЕЖИМ" << "ГОР." << "КОМАНДЫ" << "БЛОКИРОВКИ");
                ui->tableView->setModel(csvModel); // Устанавливаем модель в таблицу
                ui->tableView->setColumnWidth(0,50);
                ui->tableView->setColumnWidth(1,70);
                ui->tableView->setColumnWidth(2,30);
                ui->tableView->setColumnWidth(3,55);
                ui->tableView->setColumnWidth(4,130);
                ui->tableView->setColumnWidth(5,0);
               QString line = filename.readLine();
               // Добавляем в модель по строке с элементами
               QList<QStandardItem *> standardItemsList;

               for (QString item : line.split(";"))
               {
                   standardItemsList.append(new QStandardItem(item));
               }
               csvModel->insertRow(csvModel->rowCount(), standardItemsList);
           }

              file.close();
        }
}
