
#include "main.h"
#include "p22_ports.h"

#define SCREEN_START_ADR (0x4000)
#define SCREEN_SIZE ((256/8)*192)
#define SCREEN_ATR_SIZE (768)

volatile void irq_0x38(void);
volatile void nmi_0x66(void);

void init_screen(void);
void delay(int);

char *screen = 0x4000;
char w = 0;
char i = 0;
char key[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static volatile char irq_0x38_flag = 0;
static volatile char nmi_0x66_flag = 0;
p_0x7ffd_t p_7ffd;
p_0xeff7_t p_eff7;
char key_old = 0;
char pages[] = {6, 7};

void set_page(char page);
void set_page(char page) {
    //if((page == 2) || (page == 5)) return;
    p_7ffd.ram_page_base = page & 0x07;
    p_7ffd.ram_page_ex = (page >> 3) & 0x07;
    port_0x7ffd = *((char*)&p_7ffd);
}


void main() {
    init_screen();
    port_0x00fe = 0;
    char buff[10] = {0};
    


    while(1) {

        if(irq_0x38_flag) {
            irq_0x38_flag = 0;
            *(screen + SCREEN_SIZE-1) = i;
        }

        if(nmi_0x66_flag) {
            nmi_0x66_flag = 0;
        }

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
            print(0, 0, "fast mem test:");
            litoa(total_mem, buff);
            print(0, 15, buff);
            //delay(32768);
        }

        while(1) __asm nop __endasm;
    }
}

void init_screen(void) {
    port_0x00fe = 7;
    for (unsigned int i = SCREEN_START_ADR; i < (SCREEN_START_ADR+SCREEN_SIZE); i++) {
        *((char *)i) = 0;
    } 
    for (unsigned int i = SCREEN_START_ADR+SCREEN_SIZE; i < (SCREEN_START_ADR+SCREEN_SIZE+SCREEN_ATR_SIZE); i++) {
        *((char *)i) = 4;
    }
    port_0x00fe = 4;
}

void delay(int time) {
    for(int n = 0; n > time; n++) __asm nop __endasm;
}

volatile void irq_0x38(void) {
    irq_0x38_flag = 1;
    *(screen + SCREEN_SIZE-2) = i++;
    key[0] = port_0x7ffe;
    key[1] = port_0xeffe;
    key[2] = port_0xbffe;
    key[3] = port_0xdffe;
    key[4] = port_0xf7fe;
    key[5] = port_0xfefe;
    key[6] = port_0xfbfe;
    key[7] = port_0xfdfe;
}

volatile void nmi_0x66(void) {
    nmi_0x66_flag = 1;
    *(screen + SCREEN_SIZE-3) = i;
}
