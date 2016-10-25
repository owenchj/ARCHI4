#include "stdio.h"

__attribute__((constructor)) void  main()
{
  unsigned int num_iteration = 0;
  unsigned int cycle = 0;
  unsigned int opa = 0;
  unsigned int opb = 0;
  unsigned int status;
  unsigned int result = 0;


  char  byte;

  while(1) 
    {
      num_iteration++;
      opa = rand();
      opb = rand();
      gcd_set_opa(opa);
      gcd_set_opb(opb);
      gcd_start();
      status = 1;

      while(status)
      	{
      	  gcd_get_status(&status);
      	}

      gcd_get_result(&result);
      cycle = proctime();

      tty_printf("\num_iteration = %u\n", num_iteration);
      tty_printf("\ncycle = %u\n", cycle);
      tty_printf("\nopa = %u\n", opa);
      tty_printf("\nopb = %u\n", opb);
      tty_printf("\nresult = %u\n", result);

      tty_getc(&byte);
    }

} // end main
