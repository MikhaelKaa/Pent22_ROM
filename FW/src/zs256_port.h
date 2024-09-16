#ifndef __ZS256_PORT__
#define __ZS256_PORT__

#include "defines.h"

void ZS256_set_page(char page);

// Порт расширенной конфигурации.
__sfr __banked __at(0x1ffd) port_0x1ffd;

// Базовый порт конфигурации.
typedef struct p_0x7ffd_sc
{
    unsigned ram_page_base  : 3;
    unsigned screen         : 1;
    unsigned rom_page       : 1;
    unsigned ram_lock48     : 1;
    unsigned not_used       : 2;
}p_0x7ffd_sc_t;

// Порт расширенной конфигурации.
typedef struct p_0x1ffd
{
    unsigned ram_0_to_rom       : 1; // разряд блокировки ПЗУ в области 0…3FFFh; запись 1 разрешает запись и чтение нулевой страницы ОЗУ;
    unsigned rom_ex             : 1; // выбор ПЗУ Expansion (при использовании ПЗУ 27512), в этом ПЗУ находится основная часть теневого сервис - монитора;
    unsigned not_used0          : 1; // в настоящее время не используется;
    unsigned rs_232_out         : 1; // используется для вывода no RS - 232C (рис.11);
    unsigned centronics_strob   : 1; // сигнал стробирования для интерфейса CENTRONICS, для формирования стро
    unsigned ram_page_ex        : 1; // расширение ОЗУ; установленный разряд подключает в область адресов C000h…FFFFh страницу ОЗУ с номером от 8 до 15. Конкретный номер страницы определяется разрядами D0…D2 порта 7FFDh; 
    unsigned not_used1          : 2; // в настоящее время не используются.
}p_0x1ffd_t;

#endif /* __ZS256_PORT__ */