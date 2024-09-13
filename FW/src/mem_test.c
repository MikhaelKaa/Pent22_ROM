
#include "main.h"

void fast_mem_test(char i) {
    // Заполним начало каждой баки памяти её номером.
    for(char nw = 0; nw < 64; nw++) {
        if((nw == 2) || (nw == 5)) continue;;
        set_page(nw);
        *((char*)0xc000) = nw;
    }

    // Проверяем.
    long int total_mem = 0;
    for(char nr = 0; nr < 64; nr++) {
        if((nr == 2) || (nr == 5)) continue;;
        set_page(nr);
        if(*((char*)0xc000) == nr) total_mem+=0x4000;
        print(i, 0, "fast mem test:");
        litoa(total_mem, buff);
        print(i, 15, buff);
        //delay(32768);
    }
}
