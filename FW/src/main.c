
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
p_0x7ffd_t p_7ffd;
p_0xeff7_t p_eff7;
char key_old = 0;

void main() {
    init_screen();

    // Режим турбо можно переключить, если сначала выполнить код из ОЗУ. 
    // Без этого не получается - просто не реагирует на изменение 4 бита eff7
    port_0x7ffd = 0;
    for (unsigned int i = SCREEN_START_ADR+SCREEN_SIZE+SCREEN_ATR_SIZE; i < 65530; i++) *((char *)i) = 0;
    char *turbo_hack = (char*)25000;
    *turbo_hack = 0xc9; // 0xc9 это опкод z80 ret.
    // __asm jp 25000 __endasm; // Передаем управление на ret. И возвращаемся обратно.

    port_0x00fe = 0;
    char buff[10] = {0};

    while(1) {
        *(screen + 4) = key[0];
        *(screen + 6) = key[1];

        if(key[1] != key_old) {
            switch (key[1])
            {
            case 254: // 0
                port_0xeff7 = 16; // turbo off
                break;
            case 253: // 9
                port_0xeff7 = 0; // turbo on
                break;  
            case 251: // 8
                *turbo_hack = 0xc9; // 0xc9 это опкод z80 ret.
                __asm jp 25000 __endasm;
                break;      
            default:
                break;
            }
            key_old = key[0];
            itoa(key[1], buff);
            print(1, 0, buff);
        }


        if(irq_0x38_flag) {
            irq_0x38_flag = 0;
            // if(!(i%129)) port_0x00fe = w++;
            *(screen + 0) = i++;
        }

        if(nmi_0x66_flag) {
            nmi_0x66_flag = 0;
            char tmp = *(screen + 2);
            *(screen + 2) = tmp + 1;
            if((w&1) == 1) {
                port_0xeff7 = 16;
            } else {
                port_0xeff7 = 0;
            }
            //port_0xeff7 = *((char*)(&p_eff7));
            // port_0x00fe = w++;
            w++;
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
