
#include "main.h"

#include "general_sound.h"

#define SCREEN_START_ADR (0x4000)
#define SCREEN_SIZE ((256/8)*192)
#define SCREEN_ATR_SIZE (768)

volatile void irq_0x38(void);
volatile void nmi_0x66(void);

void init_screen(void);
void* memset(void* buf, char z, unsigned int bytes);

char *screen = 0x4000;
char w = 0;
char i = 0;
char n = 0;
char key[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static volatile char irq_0x38_flag = 0;
static volatile char nmi_0x66_flag = 0;

char key_old = 0;
char pages[] = {6, 7};

void P22_set_page(char page);


    char buff[10] = {0};

void main() {
    init_screen();
    port_0x00fe = 0;
    


    while(1) {

        if(irq_0x38_flag) {
            irq_0x38_flag = 0;
            *(screen + SCREEN_SIZE-1) = i;
        }

        if(nmi_0x66_flag) {
            nmi_0x66_flag = 0;
        }
        

        n++;
        for(char x = 0; x < 32; x++) {
            for(char y = 0; y < 24; y++) {
                print(23-y, x, (((y+x*24+n)%n)&(n/2))?(" "):("+"));
            }
        }

        //fast_mem_test(0);
        //memset(buff, 0, sizeof(buff));
        //gs_test(1);

        //while(1) __asm nop __endasm;
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

void* memset(void* buf, char z, unsigned int bytes)
{
    if (buf)
    {
       char* tmp_mem = (char*)buf;
       while (bytes--) *tmp_mem++ = z;
    }
    
    return buf;
}
