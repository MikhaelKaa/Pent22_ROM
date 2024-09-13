
#include "general_sound.h"

void gs_test(char i) {
    long int gs_total_mem = 0;
    GS_SET_CMD(GS_CMD_GET_TOTAL_RAM);
    delay(32769);
    char gtr_l = GS_GET_DAT;
    delay(32769);
    char gtr_m = GS_GET_DAT;
    delay(32769);
    char gtr_h = GS_GET_DAT;
    gs_total_mem = gtr_h*65536 + gtr_m*256 + gtr_l;
    litoa(gs_total_mem, buff);
    print(i, 0, buff);
}
