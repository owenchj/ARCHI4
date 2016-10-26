#include "stdio.h"

#define NBLOCS 32
#define THRESHOLD 200


__attribute__((constructor)) void main()
{
    char            buf_in[128*128];
    int             x;
    int             base = 0;

    while(base < 5*NBLOCS)
    {
        tty_printf("\n *** image %d *** at date = %d \n", base/NBLOCS, proctime());

/* Phase 1 : lecture image sur le disque et transfert vers buf_in */
        x = ioc_read(base, buf_in, NBLOCS);
        if(x)   {
            tty_printf("echec ioc_read = %d\n", x);
        }
        else
        {
            while(ioc_completed());
            tty_printf("ioc_read  completed at date = %d \n",proctime());
        }

/* Phase 2 : transfert de buf_out vers le frame buffer par dma */
        x = fb_write(0,buf_in,128*128);
        if(x)   {
            tty_printf("echec fb_write = %d\n", x);
        }
        else    {
            while(fb_completed());
            tty_printf("transfer completed at date = %d \n",proctime());
        }

        base = base + NBLOCS;
    } // end while
    exit();
} // end main
