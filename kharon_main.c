/*============================[[    beg-code    ]]============================*/
#include      "kharon.h"



int              /* [------] main driver -------------------------------------*/
main               (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          = 0;        /* return code (char)                  */
   /*---(initialize)---------------------*/
   if (rc >= 0)  rc = PROG_preinit ();
   if (rc >= 0)  rc = yURG_logger  (a_argc, a_argv);
   if (rc >= 0)  rc = yURG_urgs    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_init    ();
   if (rc >= 0)  rc = PROG_args    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_begin   ();
   if (rc >= 0)  rc = PROG_final   ();
   /*---(defense)------------------------*/
   DEBUG_PROG  yLOG_value   ("startup"   , rc);
   --rce;  if (rc <  0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      PROG_end ();
      return rce;
   }
   /*---(sweep for complete)-------------*/
   while (1) {
      sweep ();
      sleep (my.delay);
   }
   /*---(shutdown)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   PROG_end     ();
   /*---(complete)-----------------------*/
   return 0;
}


/*============================[[    end-code    ]]============================*/
