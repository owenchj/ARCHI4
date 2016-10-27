#include "stdio.h"

/*
 * 0x0 : Timer not activated
 * 0x1 : Timer activated, but no interrupt is generated
 * 0x3 : Timer activarted and periodic interrupts generated
 */
#define not_active_mode  0x0
#define active_mode      0x1
#define active_irq_mode  0x3

#define timer_period 50000

__attribute__((constructor)) void main_display()
{
    unsigned int ret;

    /* ret = timer_set_period(timer_period); */
    /* if(ret) */
    /* { */
    /*     tty_printf("\ntimer_set_period error\n"); */
    /* } */

    /* ret = timer_set_mode(active_irq_mode); */
    /* if(ret) */
    /* { */
    /*     tty_printf("\ntimer_set_mode error\n"); */
    /* } */

    char byte;
    while(1)
    {
        tty_getc_irq(&byte);

        if(byte == 'a')
        {
            ret = timer_set_period(timer_period);
            if(ret)
            {
                tty_printf("\ntimer_set_period error\n");
            }

            ret = timer_set_mode(active_irq_mode);
            if(ret)
            {
                tty_printf("\ntimer_set_mode error\n");
            }

            tty_puts("\nTime in active irq mode, with period 500000\n");
        }
        else if(byte == 'd')
        {
            ret = timer_reset_irq();
            if(ret)
            {
                tty_printf("\ntimer_reset_irq error\n");
            }

            ret = timer_set_mode(active_mode);
            if(ret)
            {
                tty_printf("\ntimer_set_mode error\n");
            }

            tty_puts("\nTime not in active mode\n");
        }
        else if(byte == 'q')
        {
            tty_puts("\nQuit\n");
            break;
        }

    }

    exit();
} // end main
