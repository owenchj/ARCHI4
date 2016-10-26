#include "stdio.h"

/*
 * 0x0 : Timer not activated
 * 0x1 : Timer activated, but no interrupt is generated
 * 0x3 : Timer activarted and periodic interrupts generated
 */
#define timer_mode 3
#define timer_period 500000

__attribute__((constructor)) void main()
{
    unsigned int ret;
    ret = timer_set_mode(timer_mode);
    if(ret)
    {
        tty_printf("\ntimer_set_mode error\n");
    }

    ret = timer_set_period(timer_period);
    if(ret)
    {
        tty_printf("\ntimer_set_period error\n");
    }

    exit();
} // end main
