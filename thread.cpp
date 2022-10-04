#include "thread.h"
#include <math.h>
#include <modbus.h>
#include <modbus-tcp.h>
void thread::run()
{

        tmrMB = new QTimer(this);
        tmrMB->setInterval(500);
        connect(tmrMB,  SIGNAL(timeout()),  this,  SLOT(m_Timeout()));
        connect(tmrMB,  SIGNAL(timeout()),  this,  SLOT(write_log()));
        connect(tmrMB,  SIGNAL(timeout()),  this,  SLOT(write_log_2()));
        tmrSer = new QTimer(this);
        connect(tmrSer, SIGNAL(timeout() ), this,  SLOT(dis_ser()));
        connect(this, SIGNAL(call_ser()), this, SLOT(start_tmr_ser()));
        tmrMB->start();
        ctx = modbus_new_tcp("10.0.6.10", 502);
        modbus_set_slave(ctx, 1);
        modbus_connect(ctx);
        //QSerialPort serial;
        serial.setPortName("COM2");
        serial.setBaudRate(QSerialPort::Baud1200);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
        serial.open(QIODevice::ReadWrite);
        exec();               
}
thread::~thread()
{
    tmrMB->stop();
    delete tmrMB;
}

void thread::stoptmr()
{
tmrMB->stop();
}



void thread::start_tmr_ser()
{
tmrSer->start(4000);
}

void thread::dis_ser()
{
       tmrSer->stop();
       serial.setBreakEnabled(false);
}



void thread::m_Timeout()
{
    rc = modbus_read_registers(ctx, 0, 26, tab_reg);
    emit send(rc);

    if (rc == -1)
    {
           fprintf(stderr, "%s\n", modbus_strerror(errno));
            //  return -1;
        modbus_set_error_recovery(ctx,
                                  MODBUS_ERROR_RECOVERY_PROTOCOL);
        modbus_connect(ctx);
    } else {
        for (i=0; i < rc; i++) {
            printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);}
        device_parametrs_readed.work_mode=tab_reg[0];
        device_parametrs_readed.work_signal=tab_reg[1];
        device_parametrs_readed.work_horizon=tab_reg[2];
        device_parametrs_readed.denied_horizon_0=tab_reg[3];
        device_parametrs_readed.denied_horizon_175=tab_reg[4];
        device_parametrs_readed.denied_horizon_265=tab_reg[5];
        device_parametrs_readed.connection_with_BVV=tab_reg[6];
        DI_readed.bvv_DI_1=tab_reg[7];
        DI_readed.bvv_DI_2=tab_reg[8];
        DI_readed.bvv_DI_3=tab_reg[9];
        DI_readed.bvv_DI_4=tab_reg[10];
        DI_readed.bvv_DI_5=tab_reg[11];
        DI_readed.bvv_DI_6=tab_reg[12];
        DI_readed.bvv_DI_7=tab_reg[13];
        DI_readed.bvv_DI_8=tab_reg[14];
        DI_readed.bvv_DI_9=tab_reg[15];
        DO_readed.bvv_DO_1=tab_reg[16];
        DO_readed.bvv_DO_2=tab_reg[17];
        DO_readed.bvv_DO_3=tab_reg[18];
        DO_readed.bvv_DO_4=tab_reg[19];
        DO_readed.bvv_DO_5=tab_reg[20];
        DO_readed.bvv_DO_6=tab_reg[21];
        DO_readed.bvv_DO_7=tab_reg[22];
        DO_readed.bvv_DO_8=tab_reg[23];
        DO_readed.bvv_DO_9=tab_reg[24];
        device_parametrs_readed.time_rs485=tab_reg[25];
        emit device_param(device_parametrs_readed);    
        emit bvv_in(DI_readed);
        emit bvv_out(DO_readed);
   //------------------------------------------------------------------
    }
       // return 0;
}

void thread::write_log(){

    //workmode---------------
    if (tab_reg[0]==0)
    {
              workmode = "ЛЮДИ;";
    }  else if (tab_reg[0]==1)
    {
              workmode = "ГРУЗ;";
    }  else if (tab_reg[0]==2)
    {
              workmode = "НЕГАБАРИТ;";
    }  else if (tab_reg[0]==3)
    {
              workmode = "РЕВИЗИЯ;";
    }
//horizon---------------
    if (tab_reg[2]==0)
    {         deny0l175l265 = deny0;
              horizon = "0;";
    } else if (tab_reg[2]==1){
              deny0l175l265= deny175;
              horizon = "175;";
    } else if (tab_reg[2]==2){
              deny0l175l265= deny265;
              horizon = "265;";
    }
//worksignal------------
    if (tab_reg[1]==0)
    {        worksignal = "СТОП;";
    } else if (tab_reg[1]==1){
             worksignal = "ВВЕРХ;";
    } else if (tab_reg[1]==2){
             worksignal = "Т.ВВЕРХ;";
    } else if (tab_reg[1]==3){
             worksignal = "ВНИЗ;";
    } else if (tab_reg[1]==4){
             worksignal = "Т.ВНИЗ;";
    } else if (tab_reg[1]==5){
             worksignal = "ЛЮДИ;";
    } else if (tab_reg[1]==6){
             worksignal = "БВР;";
    } else if (tab_reg[1]==7){
             worksignal = "БОЛЬНОЙ;";
    }

    QDir().mkdir("C:/DEG/log_directory/");
    //QDir().mkdir("/media/deg/archive/log_directory/");


    QDate yearnow = QDate::currentDate();
    QString yearstamp = yearnow.toString(QLatin1String("yyyy"));
    QString targetplace = QString::fromLatin1("C:/DEG/log_directory/%1").arg(yearstamp);
    QDir targetDir(targetplace);
    targetDir.cdUp();
    targetDir.mkdir(QFileInfo(targetplace).fileName());

    QDate now = QDate::currentDate();
    QString timestamp = now.toString(QLatin1String("dd.MM.yy"));
    QString filename = QString::fromLatin1("C:/DEG/log_directory/%1/%2.csv").arg(yearstamp).arg(timestamp);
    QFile file(filename);

    static uint16_t prev[64];


    if(file.open(QIODevice::Append  | QIODevice::Text))
       {
        //Если файл успешно открыт для записи
           QTextStream writeStream(&file);
           writeStream.setCodec("Windows-1251");
           writeStream.setPadChar(' ');
//------------------------------------------------------------------------------------------------------------------
           if ((tab_reg[1] & (0x00FF)) != (prev[1] & (0x00FF))) {
                 writeStream <<QString::fromLocal8Bit("%1\%2\%3\%4\%5\n")
                                                    .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                    .arg(workmode)
                                                    .arg(horizon)
                                                    .arg(worksignal)
                                                    .arg(";");
               emit send_log();
               emit scroll();
           }

           if ((tab_reg[17] & (1 << 0)) != (prev[17] & (1 << 0)))
           {
               if (tab_reg[17] & (1 << 0)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/LUDIREGIME.wav");
               }
           }
           if ((tab_reg[17] & (1 << 1)) != (prev[17] & (1 << 1)))
           {
               if (tab_reg[17] & (1 << 1)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/GRUZ.wav");
               }
           }
           if ((tab_reg[9] & (1 << 2)) != (prev[9] & (1 << 2)))
           {
               if (tab_reg[9] & (1 << 2)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/NEGABARIT.wav");
               }
           }
           if ((tab_reg[17] & (1 << 3)) != (prev[17] & (1 << 3)))
           {
               if (tab_reg[17] & (1 << 3)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/REVIZ.wav");
               }
           }

           if ((tab_reg[17] & (1 << 15)) != (prev[17] & (1 << 15)))
           {
               if (tab_reg[17] & (1 << 15)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/STOP.wav");
               }
           }
           if ((tab_reg[17] & (1 << 11)) != (prev[17] & (1 << 11)))
           {
               if (tab_reg[17] & (1 << 11)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/VERH.wav");
               }
           }
           if ((tab_reg[17] & (1 << 12)) != (prev[17] & (1 << 12)))
           {
               if (tab_reg[17] & (1 << 12)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/TVERH.wav");
               }
           }
           if ((tab_reg[17] & (1 << 13)) != (prev[17] & (1 << 13)))
           {
               if (tab_reg[17] & (1 << 13)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/VNIZ.wav");
               }
           }
           if ((tab_reg[17] & (1 << 14)) != (prev[17] & (1 << 14)))
           {
               if (tab_reg[17] & (1 << 14)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/TVNIZ.wav");
               }
           }
           if ((tab_reg[17] & (1 << 8)) != (prev[17] & (1 << 8)))
           {
               if (tab_reg[17] & (1 << 8)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/LUDI.wav");
               }
           }
           if ((tab_reg[17] & (1 << 9)) != (prev[17] & (1 << 9)))
           {
               if (tab_reg[17] & (1 << 9)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/BVR.wav");
               }
           }
           if ((tab_reg[17] & (1 << 10)) != (prev[17] & (1 << 10)))
           {
               if (tab_reg[17] & (1 << 10)){
               serial.setBreakEnabled(true);
               emit call_ser();
               QSound::play("C:/DEG/sounds/BOLNOY.wav");
               }
           }
//--------------------------------------------------ГОР 0--------------------------------------------------------------
            if ((tab_reg[1] != prev[1]) & (prev[1]>0))
{
            if ((tab_reg[3] & (1 << 5)) != (prev[3] & (1 << 5)))
            {
                if (tab_reg[3] & (1 << 5)){
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                     .arg(workmode)
                                                     .arg(horizon)
                                                     .arg(worksignal)
                                                     .arg("ПЕРЕПОДЪЕМ ЛЕВ.;");
                emit send_log();
                emit scroll();}
            }

            if ((tab_reg[3] & (1 << 12)) != (prev[3] & (1 << 12)))
            {
                if (tab_reg[3] & (1 << 12)){
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                     .arg(workmode)
                                                     .arg(horizon)
                                                     .arg(worksignal)
                                                     .arg("ПЕРЕПОДЪЕМ ПРАВ.;");
                emit send_log();
                emit scroll();}
            }
            if ((tab_reg[3] & (1 << 6)) != (prev[3] & (1 << 6)))
            {
                if (tab_reg[3] & (1 << 6)){
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                     .arg(workmode)
                                                     .arg(horizon)
                                                     .arg(worksignal)
                                                     .arg("ПЕРЕПОДЪЕМ КОП.ЛЕВ.;");
                emit send_log();
                emit scroll();}
            }
            if ((tab_reg[3] & (1 << 13)) != (prev[3] & (1 << 13)))
            {
                if (tab_reg[3] & (1 << 13)){
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                     .arg(workmode)
                                                     .arg(horizon)
                                                     .arg(worksignal)
                                                     .arg("ПЕРЕПОДЪЕМ КОП.ПРАВ.;");
                emit send_log();
                emit scroll();}
            }

            if( (tab_reg[3] & (1 << 1)) != (prev[3] & (1 << 1)))
            {
                if (tab_reg[3] & (1 << 1)){
                                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                     .arg(workmode)
                                                                     .arg(horizon)
                                                                     .arg(worksignal)
                                                                     .arg("ДВЕРИ ПЕРЕДНИЕ 1 (ГОР.0);");
                                emit send_log();
                                emit scroll();}
            }

            if( (tab_reg[3] & (1 << 8)) != (prev[3] & (1 << 8)))
            {
                if (tab_reg[3] & (1 << 8)){
                                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                     .arg(workmode)
                                                                     .arg(horizon)
                                                                     .arg(worksignal)
                                                                     .arg("ДВЕРИ ПЕРЕДНИЕ 2 (ГОР.0);");
                                emit send_log();
                                emit scroll();}

            }
            if( (tab_reg[3] & (1 << 2)) != (prev[3] & (1 << 2)))
            {
                if (tab_reg[3] & (1 << 2)){
                                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                     .arg(workmode)
                                                                     .arg(horizon)
                                                                     .arg(worksignal)
                                                                     .arg("ДВЕРИ ЗАДНИЕ 1 (ГОР.0);");
                                emit send_log();
                                emit scroll();}

            }
            if( (tab_reg[3] & (1 << 9)) != (prev[3] & (1 << 9)))
            {
                if (tab_reg[3] & (1 << 9)){
                                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                     .arg(workmode)
                                                                     .arg(horizon)
                                                                     .arg(worksignal)
                                                                     .arg("ДВЕРИ ЗАДНИЕ 2 (ГОР.0);");
                                emit send_log();
                                emit scroll();}

            }



            if( (tab_reg[3] & (1 << 3)) != (prev[3] & (1 << 3)))
            {
                if (tab_reg[3] & (1 << 3)){
                                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                     .arg(workmode)
                                                                     .arg(horizon)
                                                                     .arg(worksignal)
                                                                     .arg("КУЛАКИ УБРАНЫ ЛЕВ.;");
                                emit send_log();
                                emit scroll();}else{
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("КУЛАКИ ВЫДВИНУТЫ ЛЕВ.;");
                    emit send_log();
                    emit scroll();}

            }

            if( (tab_reg[3] & (1 << 10)) != (prev[3] & (1 << 10)))
            {
                if (tab_reg[3] & (1 << 10)){
                                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                     .arg(workmode)
                                                                     .arg(horizon)
                                                                     .arg(worksignal)
                                                                     .arg("КУЛАКИ УБРАНЫ ПРАВ;");
                                emit send_log();
                                emit scroll();}else{
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("КУЛАКИ ВЫДВИНУТЫ ПРАВ.;");
                    emit send_log();
                    emit scroll();}

            }
    }
//----------------------------------------------------------------------------------------------------

            if  ((tab_reg[3] & (1 << 4)) != (prev[3] & (1 << 4)))
            {
                if (tab_reg[3] & (1 << 4)){
                                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                     .arg(workmode)
                                                                     .arg(horizon)
                                                                     .arg(worksignal)
                                                                     .arg("ЛЯДЫ ЛЕВ.КЛЕТЬ (ГОР.0);");
                                emit send_log();
                                emit scroll();}

            }
            if  ((tab_reg[3] & (1 << 11)) != (prev[3] & (1 << 11)))
            {
                if (tab_reg[3] & (1 << 11)){
                                writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                     .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                     .arg(workmode)
                                                                     .arg(horizon)
                                                                     .arg(worksignal)
                                                                     .arg("ЛЯДЫ ПРАВ.КЛЕТЬ (ГОР.0);");
                                emit send_log();
                                emit scroll();}

            }
//------------------------------------------------ГОР 175------------------------------------------------------------------
            if ((tab_reg[1] != prev[1]) & (prev[1]>0))
{
            if ((tab_reg[4] & (1 << 1)) != (prev[4] & (1 << 1)))
            {
                if (tab_reg[4] & (1 << 1)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("ДВЕРИ ПЕРЕДНИЕ 1 (ГОР.175);");
                    emit send_log();
                    emit scroll();}

            }

            if ((tab_reg[4] & (1 << 3)) != (prev[4] & (1 << 3)))
            {
                if (tab_reg[4] & (1 << 3)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("ДВЕРИ ПЕРЕДНИЕ 2 (ГОР.175);");
                    emit send_log();
                    emit scroll();}

            }
}
//-------------------------------------------------------ГОР 265-----------------------------------------------------------
            if ((tab_reg[1] != prev[1]) & (prev[1]>0))
{
            if ((tab_reg[5] & (1 << 1)) != (prev[5] & (1 << 1)))
            {
                if (tab_reg[5] & (1 << 1)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("ДВЕРИ ПЕРЕДНИЕ 1 (ГОР.265);");
                    emit send_log();
                    emit scroll();}
            }
            if ((tab_reg[5] & (1 << 2)) != (prev[5] & (1 << 2)))
            {
                if (tab_reg[5] & (1 << 2)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("ДВЕРИ ЗАДНИЕ 1 (ГОР.265);");
                    emit send_log();
                    emit scroll();}
            }
            if ((tab_reg[5] & (1 << 5)) != (prev[5] & (1 << 5)))
            {
                if (tab_reg[5] & (1 << 5)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("ДВЕРИ ПЕРЕДНИЕ 2 (ГОР.265);");
                    emit send_log();
                    emit scroll();}
            }
            if ((tab_reg[5] & (1 << 6)) != (prev[5] & (1 << 6)))
            {
                if (tab_reg[5] & (1 << 6)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("ДВЕРИ ЗАДНИЕ 2 (ГОР.265);");
                    emit send_log();
                    emit scroll();}
            }
}
//--------------------------------------------------------------------------------
            if ((tab_reg[5] & (1 << 3)) != (prev[5] & (1 << 3)))
            {
                if (tab_reg[5] & (1 << 3)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("ТОРМОЗ. КАНАТЫ ЛЕВ.КЛЕТИ (ГОР.265);");
                    emit send_log();
                    emit scroll();}
            }
            if ((tab_reg[5] & (1 << 7)) != (prev[5] & (1 << 7)))
            {
                if (tab_reg[5] & (1 << 7)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("ТОРМОЗ. КАНАТЫ ПРАВ.КЛЕТИ (ГОР.265);");
                    emit send_log();
                    emit scroll();}
            }

//---------------------------------------------------------------------------------------------------------------------
            if ((tab_reg[9] & (1 << 7)) != (prev[9] & (1 << 7)))
            {
                if (tab_reg[9] & (1 << 7)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("АВАР.СТОП РУКОЯТКА ВЫКЛ ;");
                    emit send_log();
                    emit scroll();} else
                {
                                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                         .arg(workmode)
                                                                         .arg(horizon)
                                                                         .arg(worksignal)
                                                                         .arg("АВАР.СТОП РУКОЯТКА ВКЛ ;");
                                    emit send_log();
                                    emit scroll();}
            }

            if ((tab_reg[15] & (1 << 0)) != (prev[15] & (1 << 0)))
            {
                if (tab_reg[15] & (1 << 0)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("АВАР.СТОП ПОМОЩНИК ВЫКЛ;");
                    emit send_log();
                    emit scroll();}else
                {
                                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                         .arg(workmode)
                                                                         .arg(horizon)
                                                                         .arg(worksignal)
                                                                         .arg("АВАР.СТОП ПОМОЩНИК ВКЛ ;");
                                    emit send_log();
                                    emit scroll();}
            }

            if ((tab_reg[11] & (1 << 7)) != (prev[11] & (1 << 7)))
            {
                if (tab_reg[11] & (1 << 7)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("АВАР.СТОП 175 ВЫКЛ;");
                    emit send_log();
                    emit scroll();}else
                {
                                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                         .arg(workmode)
                                                                         .arg(horizon)
                                                                         .arg(worksignal)
                                                                         .arg("АВАР.СТОП 175 ВКЛ ;");
                                    emit send_log();
                                    emit scroll();}
            }
            if ((tab_reg[13] & (1 << 7)) != (prev[13] & (1 << 7)))
            {
                if (tab_reg[13] & (1 << 7)){
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                         .arg(workmode)
                                                         .arg(horizon)
                                                         .arg(worksignal)
                                                         .arg("АВАР.СТОП 265 ВЫКЛ;");
                    emit send_log();
                    emit scroll();}else
                {
                                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                         .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                         .arg(workmode)
                                                                         .arg(horizon)
                                                                         .arg(worksignal)
                                                                         .arg("АВАР.СТОП 265 ВКЛ ;");
                                    emit send_log();
                                    emit scroll();}
            }
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
            if( (tab_reg[6] & (1 << 0)) != (prev[6] & (1 << 0)) ){

              if (prev[6] & (1 << 0)) {
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                               .arg(QTime::currentTime().toString("hh:mm:ss;"))
                               .arg(";")
                               .arg(";")
                               .arg(";")
                               .arg("ОБРЫВ СВЯЗИ БВВ 1 Пульт Машиниста;");
emit send_log();
emit scroll();}
}
            if( (tab_reg[6] & (1 << 1)) != (prev[6] & (1 << 1)) ){

              if (prev[6] & (1 << 1)) {
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                               .arg(QTime::currentTime().toString("hh:mm:ss;"))
                               .arg(";")
                               .arg(";")
                               .arg(";")
                               .arg("ОБРЫВ СВЯЗИ БВВ 2 Пульт Машиниста;");
emit send_log();
emit scroll();}
}
            if( (tab_reg[6] & (1 << 2)) != (prev[6] & (1 << 2)) ){

              if (prev[6] & (1 << 2)) {
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                               .arg(QTime::currentTime().toString("hh:mm:ss;"))
                               .arg(";")
                               .arg(";")
                               .arg(";")
                               .arg("ОБРЫВ СВЯЗИ БВВ 3 Пульт рукоятки;");
emit send_log();
emit scroll();}
}
            if( (tab_reg[6] & (1 << 3)) != (prev[6] & (1 << 3)) ){

              if (prev[6] & (1 << 3)) {
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                               .arg(QTime::currentTime().toString("hh:mm:ss;"))
                               .arg(";")
                               .arg(";")
                               .arg(";")
                               .arg("ОБРЫВ СВЯЗИ БВВ 4 Пульт рукоятки;");
emit send_log();
emit scroll();}
}
            if( (tab_reg[6] & (1 << 4)) != (prev[6] & (1 << 4)) ){

              if (prev[6] & (1 << 4)) {
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                               .arg(QTime::currentTime().toString("hh:mm:ss;"))
                               .arg(";")
                               .arg(";")
                               .arg(";")
                               .arg("ОБРЫВ СВЯЗИ БВВ 5 (ГОР. 175);");
emit send_log();
emit scroll();}
}
            if( (tab_reg[6] & (1 << 5)) != (prev[6] & (1 << 5)) ){

              if (prev[6] & (1 << 5)) {
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                               .arg(QTime::currentTime().toString("hh:mm:ss;"))
                               .arg(";")
                               .arg(";")
                               .arg(";")
                               .arg("ОБРЫВ СВЯЗИ БВВ 6 (ГОР. 175);");
emit send_log();
emit scroll();}
}
            if( (tab_reg[6] & (1 << 6)) != (prev[6] & (1 << 6)) ){

              if (prev[6] & (1 << 6)) {
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                               .arg(QTime::currentTime().toString("hh:mm:ss;"))
                               .arg(";")
                               .arg(";")
                               .arg(";")
                               .arg("ОБРЫВ СВЯЗИ БВВ 7 (ГОР. 265);");
emit send_log();
emit scroll();}
}
            if( (tab_reg[6] & (1 << 7)) != (prev[6] & (1 << 7)) ){

              if (prev[6] & (1 << 7)) {
                writeStream <<QString("%1\%2\%3\%4\%5\n")
                               .arg(QTime::currentTime().toString("hh:mm:ss;"))
                               .arg(";")
                               .arg(";")
                               .arg(";")
                               .arg("ОБРЫВ СВЯЗИ БВВ 8 (ГОР. 265);");
emit send_log();
emit scroll();}
}  
                if( (tab_reg[6] & (1 << 8)) != (prev[6] & (1 << 8)) ){

                  if (prev[6] & (1 << 8)) {
                    writeStream <<QString("%1\%2\%3\%4\%5\n")
                                   .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                   .arg(";")
                                   .arg(";")
                                   .arg(";")
                                   .arg("ОБРЫВ СВЯЗИ БВВ 9 Пульт помощника;");
    emit send_log();
    emit scroll();}
    }
             static int rc_prev;
             if ( rc != rc_prev) {
                 if (rc == -1) { writeStream <<QString("%1\%2\%3\%4\%5\n")
                                               .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                               .arg(";")
                                               .arg(";")
                                               .arg(";")
                                               .arg("ОБРЫВ СВЯЗИ С ПЛК;");
                emit send_log();
                emit scroll();} else
                 { writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                                .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                                .arg(";")
                                                                .arg(";")
                                                                .arg(";")
                                                                .arg("УСТАНОВКА СВЯЗИ С ПЛК;");
                                 emit send_log();
                                 emit scroll();}
             }
//--------------------------------------------------------------------------------------------------------------------
        file.close(); // Закрываем файл
        prev[0] = tab_reg[0];
        prev[1] = tab_reg[1];
        prev[2] = tab_reg[2];
        prev[3] = tab_reg[3];
        prev[4] = tab_reg[4];
        prev[5] = tab_reg[5];
        prev[6] = tab_reg[6];
        prev[7] = tab_reg[7];
        prev[8] = tab_reg[8];
        prev[9] = tab_reg[9];
        prev[10] = tab_reg[10];
        prev[11] = tab_reg[11];
        prev[12] = tab_reg[12];
        prev[13] = tab_reg[13];
        prev[14] = tab_reg[14];
        prev[15] = tab_reg[15];
        prev[16] = tab_reg[16];
        prev[17] = tab_reg[17];
        prev[18] = tab_reg[18];
        prev[19] = tab_reg[19];
        prev[20] = tab_reg[20];
        prev[21] = tab_reg[21];
        prev[22] = tab_reg[22];
        prev[23] = tab_reg[23];
        prev[24] = tab_reg[24];
        rc_prev = rc;

     }

}
void thread::write_log_2(){
    QDir().mkdir("C:/DEG/log_PLC_BVV/");

    QDate yearnow = QDate::currentDate();
    QString yearstamp = yearnow.toString(QLatin1String("yyyy"));
    QString targetplace = QString::fromLatin1("C:/DEG/log_PLC_BVV/%1").arg(yearstamp);
    QDir targetDir(targetplace);
    targetDir.cdUp();
    targetDir.mkdir(QFileInfo(targetplace).fileName());

    QDate now = QDate::currentDate();
    QString timestamp = now.toString(QLatin1String("dd.MM.yy"));
    QString filename = QString::fromLatin1("C:/DEG/log_PLC_BVV/%1/%2.csv").arg(yearstamp).arg(timestamp);
    QFile file(filename);

    static uint16_t prev[64];
    if(file.open(QIODevice::Append  | QIODevice::Text))
       {
        //Если файл успешно открыт для записи
           QTextStream writeStream(&file);
           writeStream.setCodec("Windows-1251");
           writeStream.setPadChar(' ');

           if( (tab_reg[6] & (1 << 0)) != (prev[6] & (1 << 0)) ){

             if (prev[6] & (1 << 0)) {
               writeStream <<QString("%1\%2\%3\%4\%5\n")
                              .arg(QTime::currentTime().toString("hh:mm:ss;"))
                              .arg(";")
                              .arg(";")
                              .arg(";")
                              .arg("ОБРЫВ СВЯЗИ БВВ 1 Пульт Машиниста;");
emit send_log_2();
emit scroll();}
}
           if( (tab_reg[6] & (1 << 1)) != (prev[6] & (1 << 1)) ){

             if (prev[6] & (1 << 1)) {
               writeStream <<QString("%1\%2\%3\%4\%5\n")
                              .arg(QTime::currentTime().toString("hh:mm:ss;"))
                              .arg(";")
                              .arg(";")
                              .arg(";")
                              .arg("ОБРЫВ СВЯЗИ БВВ 2 Пульт Машиниста;");
emit send_log_2();
emit scroll();}
}
           if( (tab_reg[6] & (1 << 2)) != (prev[6] & (1 << 2)) ){

             if (prev[6] & (1 << 2)) {
               writeStream <<QString("%1\%2\%3\%4\%5\n")
                              .arg(QTime::currentTime().toString("hh:mm:ss;"))
                              .arg(";")
                              .arg(";")
                              .arg(";")
                              .arg("ОБРЫВ СВЯЗИ БВВ 3 Пульт рукоятки;");
emit send_log_2();
emit scroll();}
}
           if( (tab_reg[6] & (1 << 3)) != (prev[6] & (1 << 3)) ){

             if (prev[6] & (1 << 3)) {
               writeStream <<QString("%1\%2\%3\%4\%5\n")
                              .arg(QTime::currentTime().toString("hh:mm:ss;"))
                              .arg(";")
                              .arg(";")
                              .arg(";")
                              .arg("ОБРЫВ СВЯЗИ БВВ 4 Пульт рукоятки;");
emit send_log_2();
emit scroll();}
}
           if( (tab_reg[6] & (1 << 4)) != (prev[6] & (1 << 4)) ){

             if (prev[6] & (1 << 4)) {
               writeStream <<QString("%1\%2\%3\%4\%5\n")
                              .arg(QTime::currentTime().toString("hh:mm:ss;"))
                              .arg(";")
                              .arg(";")
                              .arg(";")
                              .arg("ОБРЫВ СВЯЗИ БВВ 5 (ГОР. 175);");
emit send_log_2();
emit scroll();}
}
           if( (tab_reg[6] & (1 << 5)) != (prev[6] & (1 << 5)) ){

             if (prev[6] & (1 << 5)) {
               writeStream <<QString("%1\%2\%3\%4\%5\n")
                              .arg(QTime::currentTime().toString("hh:mm:ss;"))
                              .arg(";")
                              .arg(";")
                              .arg(";")
                              .arg("ОБРЫВ СВЯЗИ БВВ 6 (ГОР. 175);");
emit send_log_2();
emit scroll();}
}
           if( (tab_reg[6] & (1 << 6)) != (prev[6] & (1 << 6)) ){

             if (prev[6] & (1 << 6)) {
               writeStream <<QString("%1\%2\%3\%4\%5\n")
                              .arg(QTime::currentTime().toString("hh:mm:ss;"))
                              .arg(";")
                              .arg(";")
                              .arg(";")
                              .arg("ОБРЫВ СВЯЗИ БВВ 7 (ГОР. 265);");
emit send_log_2();
emit scroll();}
}
           if( (tab_reg[6] & (1 << 7)) != (prev[6] & (1 << 7)) ){

             if (prev[6] & (1 << 7)) {
               writeStream <<QString("%1\%2\%3\%4\%5\n")
                              .arg(QTime::currentTime().toString("hh:mm:ss;"))
                              .arg(";")
                              .arg(";")
                              .arg(";")
                              .arg("ОБРЫВ СВЯЗИ БВВ 8 (ГОР. 265);");
emit send_log_2();
emit scroll();}
}
               if( (tab_reg[6] & (1 << 8)) != (prev[6] & (1 << 8)) ){

                 if (prev[6] & (1 << 8)) {
                   writeStream <<QString("%1\%2\%3\%4\%5\n")
                                  .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                  .arg(";")
                                  .arg(";")
                                  .arg(";")
                                  .arg("ОБРЫВ СВЯЗИ БВВ 9 Пульт помощника;");
   emit send_log_2();
   emit scroll();}
   }
            static int rc_prev;
            if ( rc != rc_prev) {
                if (rc == -1) { writeStream <<QString("%1\%2\%3\%4\%5\n")
                                              .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                              .arg(";")
                                              .arg(";")
                                              .arg(";")
                                              .arg("ОБРЫВ СВЯЗИ С ПЛК;");
               emit send_log_2();
               emit scroll();} else
                { writeStream <<QString("%1\%2\%3\%4\%5\n")
                                                               .arg(QTime::currentTime().toString("hh:mm:ss;"))
                                                               .arg(";")
                                                               .arg(";")
                                                               .arg(";")
                                                               .arg("УСТАНОВКА СВЯЗИ С ПЛК;");
                                emit send_log_2();
                                emit scroll();}
            }


//--------------------------------------------------------------------------------------------------------------------
        file.close(); // Закрываем файл
        prev[6] = tab_reg[6];
        rc_prev = rc;
     }
}
