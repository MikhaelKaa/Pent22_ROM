
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
        memset(buff, 0, sizeof(buff));
        delay(32768);
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
p_0x1ffd_t p_0x1ffd = {
    .ram_0_to_rom = 0,
    .ram_page_ex = 0,
    .rom_ex = 0,
    .not_used0 = 0,
    .not_used1 = 0,
    .rs_232_out = 0,
    .centronics_strob = 0
};

void ZS256_set_page(char page) {
    itoa(page, buff);
    print(5, 0, buff);
    memset(buff, 0, sizeof(buff));
    p_7ffd_sc256.ram_page_base = page & (char)0x07;
    port_0x7ffd = *((char*)&p_7ffd_sc256);

    // if(page > 7) p_0x1ffd.ram_page_ex = 1;
    // else         p_0x1ffd.ram_page_ex = 0;
    
    p_0x1ffd.ram_page_ex = page & 0x08;
    itoa((char)p_0x1ffd.ram_page_ex, buff);
    print(6, 0, buff);
    memset(buff, 0, sizeof(buff));
    //p_0x1ffd.ram_page_ex = 1; // TODO
    port_0x1ffd = *((char*)&p_0x1ffd);
}