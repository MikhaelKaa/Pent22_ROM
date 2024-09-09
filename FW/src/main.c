
#include "main.h"
#include "p22_ports.h"

#define SCREEN_START_ADR (0x4000)
#define SCREEN_SIZE ((256/8)*192)
#define SCREEN_ATR_SIZE (768)

void init_screen(void);
char *screen = 0x4000;
char w = 0;
char i = 0;
char key[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static volatile char irq_0x38_flag = 0;
static volatile char nmi_0x66_flag = 0;
p_ox7ffd_t p_7ffd;

void main() {

    init_screen();
    port_0x00fe = 0;
    char buff[10] = {0};
    
    while(1) {
        *(screen + 4) = key[0];
        *(screen + 6) = key[1];

        itoa(w, buff);
        print(1, 0, buff);

        if(irq_0x38_flag) {
            irq_0x38_flag = 0;
            // if(!(i%129)) port_0x00fe = w++;
            *(screen + 0) = i++;
        }

        if(nmi_0x66_flag) {
            nmi_0x66_flag = 0;
            char tmp = *(screen + 2);
            *(screen + 2) = tmp + 1;
            w++;
            p_7ffd.screen = w;
            port_0x7ffd = *((char*)(&p_7ffd));
            // port_0x00fe = w++;
        }
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

volatile void irq_0x38(void) {
    irq_0x38_flag = 1;

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
}
