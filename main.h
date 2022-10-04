#ifndef MAIN_H
#define MAIN_H

#include <QWidget>
#include <QDebug>
#include <QThread>


struct device_parametrs{
    uint16_t    work_mode;
    uint16_t    work_signal;
    uint16_t    work_horizon;
    uint16_t    denied_horizon_0;
    uint16_t    denied_horizon_175;
    uint16_t    denied_horizon_265;
    uint16_t    connection_with_BVV;
    uint16_t    time_rs485;
};

struct bvv_DI {
    uint16_t    bvv_DI_1;
    uint16_t    bvv_DI_2;
    uint16_t    bvv_DI_3;
    uint16_t    bvv_DI_4;
    uint16_t    bvv_DI_5;
    uint16_t    bvv_DI_6;
    uint16_t    bvv_DI_7;
    uint16_t    bvv_DI_8;
    uint16_t    bvv_DI_9;
};

struct bvv_DO {
    uint16_t    bvv_DO_1;
    uint16_t    bvv_DO_2;
    uint16_t    bvv_DO_3;
    uint16_t    bvv_DO_4;
    uint16_t    bvv_DO_5;
    uint16_t    bvv_DO_6;
    uint16_t    bvv_DO_7;
    uint16_t    bvv_DO_8;
    uint16_t    bvv_DO_9;
};




#endif // MAIN_H
