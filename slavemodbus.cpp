#include "slavemodbus.h"
#include "main.h"
#include "mainwindow.h"
#include "thread.h"
#include <stdio.h>

void slavemodbus::run()
{
  /*  ctx = modbus_new_rtu("COM2", 57600, 'N', 8, 1);
    if (ctx == NULL) {
        fprintf(stderr, "Unable to create the libmodbus context\n");}
    sc = modbus_set_slave(ctx, 1);
    modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS485);
    mb_mapping = modbus_mapping_new(16, 16, 16, 16);
    if (mb_mapping == NULL) {
        fprintf(stderr, "Failed to allocate the mapping: %s\n",
                modbus_strerror(errno));}
    modbus_connect(ctx);
    exec(); */
}
//------------------------------------------------------
slavemodbus::~slavemodbus()
{
}
//------------------------------------------------------
/*void slavemodbus::plc_out(PLC par)
{
    mb_mapping->tab_registers[0] = par.PLC_0;
    mb_mapping->tab_registers[1] = par.PLC_1;
    mb_mapping->tab_registers[2] = par.PLC_2;
    mb_mapping->tab_registers[3] = par.PLC_3;
    mb_mapping->tab_registers[4] = par.PLC_4;
    mb_mapping->tab_registers[5] = par.PLC_5;
    mb_mapping->tab_registers[6] = par.PLC_6;
    mb_mapping->tab_registers[7] = par.PLC_7;
    mb_mapping->tab_registers[8] = par.PLC_8;
    mb_mapping->tab_registers[9] = par.PLC_9;
    mb_mapping->tab_registers[10] = par.PLC_10;
    mb_mapping->tab_registers[11] = par.PLC_11;
    mb_mapping->tab_registers[12] = par.PLC_12;
    rc = modbus_receive(ctx, query);
    if (rc > 0) {modbus_reply(ctx, query, rc, mb_mapping);}
     else if (rc  == -1) { modbus_connect(ctx);}
} */
