#include "main.h"
#include "font.h"

void print(char x, char y, char* text) __naked {
    NO_WARN(x);
    NO_WARN(y);
    NO_WARN(text);
    __asm
    ld iy, #2
    add iy, sp
    ld d, 0(iy)   ;x
    ld e, 1(iy)   ;y
    ld l, 2(iy)
    ld h, 3(iy)
print_string:
    //get_adr_on_screen
    ld a,d
    and #7
    rra
    rra
    rra
    rra
    or e
    ld e,a
    ld a,d
    and #24
    or #64
    ld d,a
print_string_loop:
    ld a, (hl)
    and a
    ret z
    push hl
    ld h, #0
    ld l, a
    add hl, hl
    add hl, hl
    add hl, hl
    ld bc, #_src_font_en_ch8 - #256 ;
    add hl, bc
    push de
    call print_char
    pop de
    pop hl

    xor a   
    ld (hl), a 

    inc hl
    inc de
    jp print_string_loop
    ret

print_char:
    ld b, #8
pchar_loop:
    ld a, (hl)
    ld (de), a
    inc d
    inc hl
    djnz pchar_loop
    ret
    __endasm;
}

/* Function return size of string and convert signed  *
 * integer to ascii value and store them in array of  *
 * character with NULL at the end of the array        */

int itoa(int value, char *ptr)
{
    int count = 0, temp;
    // Проверка на нулевой указатель. Просто не передавайте сюда нулевой указатель.
    // if(ptr == NULL)
    //     return 0;
    if(value == 0)
    {
        *ptr = '0';
        return 1;
    }

    if(value < 0)
    {
        value = (-1);
        *ptr++ = '-';
        count++;
    }

    for(temp=value; temp>0; temp/=10, ptr++);
        *ptr = '\0';

    for(temp=value; temp>0; temp/=10)
    {
        *--ptr = temp%10 + '0';
        count++;
    }
    return count;
}


int litoa(long int value, char *ptr)
{
    long int count = 0, temp;
    // Проверка на нулевой указатель. Просто не передавайте сюда нулевой указатель.
    // if(ptr == NULL)
    //     return 0;
    if(value == 0)
    {
        *ptr = '0';
        return 1;
    }

    if(value < 0)
    {
        value = (-1);
        *ptr++ = '-';
        count++;
    }

    for(temp=value; temp>0; temp/=10, ptr++);
        *ptr = '\0';

    for(temp=value; temp>0; temp/=10)
    {
        *--ptr = temp%10 + '0';
        count++;
    }
    return count;
}