/*============================[[    beg-code    ]]============================*/
#include      "kharon.h"



int              /* [------] main driver -------------------------------------*/
main               (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          = 0;        /* return code (char)                  */
   /*---(initialize)---------------------*/
   if (rc >= 0)  rc = yURG_logger  (a_argc, a_argv);
   if (rc >= 0)  rc = yURG_urgs    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_init    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_args    (a_argc, a_argv);
   /*---(defense)------------------------*/
   DEBUG_PROG  yLOG_value   ("startup"   , rc);
   if (rc <  0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rc);
      PROG_end ();
      return rc;
   }
   /*---(daemon mode)--------------------*/
   rc = PROG_daemon ();
   DEBUG_PROG  yLOG_value   ("daemon"    , rc);
   if (rc < 0)  {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(sweep for complete)-------------*/
   while (1) {
      yEXEC_heartbeat (my.pid, time (NULL), FILE_HEARTBEAT, my.heartbeat);
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
