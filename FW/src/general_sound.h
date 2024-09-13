#ifndef __GS__
#define __GS__

#include "main.h"

void gs_test(char i);

// Порт регистр команд/статуса General Sound.
__sfr __banked __at(0x00bb) port_0x00bb;
// Порт регистр данных General Sound.
__sfr __banked __at(0x00b3) port_0x00b3;
// Порт отключения ZXMGeneralSound. 4 бит. 
// http://micklab.ru/My%20Soundcard/ZXMGeneralSound.htm
__sfr __banked __at(0x0033) port_0x0033;

#define GS_SET_CMD(x)           (port_0x00bb = x)
#define GS_GET_DAT              port_0x00b3

#define GS_CMD_RESET_FLAGS      (0x00)
#define GS_CMD_SET_SILENCE      (0x01)
#define GS_CMD_SET_LOW_VOL      (0x02)
#define GS_CMD_SET_HIGH_VOL     (0x03)
// ... чаcть пропущена
#define GS_CMD_COVOX_MODE       (0x0E)
// ... чаcть пропущена
/* 
    SC #20
    WC
    GD RAM.L(Младшая часть)
    WN
    GD RAM.M(Средняя часть)
    WN
    GD RAM.H(Старшая часть)

Total RAM=65536*RAM.H+256*RAM.M+RAM.L
 */
#define GS_CMD_GET_TOTAL_RAM    0x20



#endif /* __GS__ */