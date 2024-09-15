
#include "main.h"
#include "p22_ports.h"
#include "zs256_port.h"

void (*set_page)(char page) = ZS256_set_page;

void fast_mem_test(char i) {
    // Заполним начало каждой баки памяти её номером.
    for(char nw = 0; nw < 64; nw++) {
        if((nw == 2) || (nw == 5)) continue;;
        ZS256_set_page(nw);
        *((char*)0xc000) = nw;
    }

    // Проверяем.
    long int total_mem = 0;
    for(char nr = 0; nr < 64; nr++) {
        if((nr == 2) || (nr == 5)) continue;;
        ZS256_set_page(nr);
        if(*((char*)0xc000) == nr) total_mem+=0x4000;
        print(i, 0, "fast mem test:");
        litoa(total_mem, buff);
        print(i, 15, buff);
        //delay(32768);
    }
}

p_0x7ffd_p22_t p_7ffd_p22;
p_0xeff7_t p_eff7;

void P22_set_page(char page) {
    //if((page == 2) || (page == 5)) return;
    p_7ffd_p22.ram_page_base = page & 0x07;
    p_7ffd_p22.ram_page_ex = (page >> 3) & 0x07;
    port_0x7ffd = *((char*)&p_7ffd_p22);
}

p_0x7ffd_sc_t p_7ffd_sc256;
p_0x1ffd_t p_0x1ffd;

void ZS256_set_page(char page) {
    //p_7ffd_sc256.ram_page_base = page & 0x07;
    //port_0x7ffd = *((char*)&p_7ffd_sc256);
    //p_0x1ffd.ram_page_ex = (page >> 3) & 0x01;
    //port_0x1ffd = *((char*)&p_0x1ffd);
}