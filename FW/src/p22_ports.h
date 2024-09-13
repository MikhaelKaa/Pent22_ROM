#ifndef __P22_PORTS__
#define __P22_PORTS__

#include "defines.h"

// Базовый порт конфигурации.
//__sfr __banked __at(0x7ffd) port_0x7ffd;
// Порт расширенной конфигурации.
__sfr __banked __at(0xeff7) port_0xeff7;

// Базовый порт конфигурации.
typedef struct p_ox7ffd
{
    unsigned ram_page_base  : 3;
    unsigned screen         : 1;
    unsigned rom_page       : 1;
    unsigned ram_page_ex    : 3;
}p_0x7ffd_t;

// Порт расширенной конфигурации.
typedef struct p_oxeff7
{
    unsigned color_16       : 1; // Включение режима 16 colour (0 – выкл, 1 – вкл.)
    unsigned not_used_0     : 1; // Не используется
    unsigned lock_ex_ram    : 1; // Включение режима 128k. При Bit 2 = 1 память сверх 128k блокируется, а на место bit 5 7FFDh встает защелка 48k.
    unsigned ram_page_0     : 1; // Блокировка ПЗУ. При bit 3 = 1 с адреса 0000h вместо ПЗУ проецируется 0-я страница ОЗУ
    unsigned turbo          : 1; // Отключение режима TURBO. При bit 4 = 0 TURBO включено, при bit 4 = 1 TURBO отключено.
    unsigned not_used_1     : 1; // Не используется
    unsigned video_mode_ex  : 1; // Включение расширенного видео режима (384x304 или 320х256 DDP). (0 – выкл, 1 – вкл.)
    unsigned not_used_2     : 1; // Не используется

}p_0xeff7_t;

#endif /* __P22_PORTS__ */