/*============================[[    beg-code    ]]============================*/
#include      "kharon.h"



tACCESSOR   my;



/*====================------------------------------------====================*/
/*===----                   standard program functions                 ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char*        /*--: return versioning information ---------[ leaf-- [ ------ ]-*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __CBANG__  > 0
   strncpy (t, "[cbang      ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (my.version, 200, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return my.version;
}

char         /*--> pre-debugging code --------------------[ leaf   [ ------ ]-*/
PROG_preinit       (void)
{
   return 0;
}

char         /*--> pre-argument processing ---------------[ leaf   [ ------ ]-*/
PROG_init          (void)
{
   /*---(locals)-----------+-------------*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(begin)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_info    ("namesake", P_NAMESAKE);
   DEBUG_TOPS   yLOG_info    ("heritage", P_HERITAGE);
   DEBUG_TOPS   yLOG_info    ("imagery" , P_IMAGERY);
   DEBUG_TOPS   yLOG_info    ("purpose" , P_PURPOSE);
   DEBUG_PROG   yLOG_info    ("kharon"  , PROG_version  ());
   DEBUG_PROG   yLOG_info    ("yEXEC"   , yEXEC_version ());
   DEBUG_PROG   yLOG_info    ("ySTR"    , ySTR_version  ());
   DEBUG_PROG   yLOG_info    ("yURG"    , yURG_version  ());
   DEBUG_PROG   yLOG_info    ("yLOG"    , yLOG_version  ());
   /*---(call whoami)--------------------*/
   rc = yEXEC_whoami (&my.pid, &my.ppid, &my.uid, NULL, &my.who, 'n');
   DEBUG_TOPS   yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_TOPS   yLOG_value   ("pid"       , my.pid);
   DEBUG_TOPS   yLOG_value   ("ppid"      , my.ppid);
   DEBUG_TOPS   yLOG_value   ("uid"       , my.uid);
   DEBUG_TOPS   yLOG_info    ("who"       , my.who);
   /*---(check for root)-----------------*/
   --rce;  if (my.uid != 0) {
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defaults)-----------------------*/
   my.delay    = 15;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> evaluate command line arguments -------[ leaf   [ ------ ]-*/
PROG_args          (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;        /* loop iterator -- arguments          */
   char       *a           = NULL;     /* current argument                    */
   int         n           = 0;        /* count of arguments                  */
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(process)------------------------*/
   for (i = 1; i < a_argc; ++i) {
      /*---(assign)----------------------*/
      a = a_argv [i];
      /*---(filter)----------------------*/
      if (a[0] == '@')       continue;
      /*---(process)---------------------*/
      DEBUG_ARGS   yLOG_info    ("argument"  , a);
      if      (strncmp (a, "--rapid"     , 12) == 0)     my.delay   =   1;
      else if (strncmp (a, "--moderate"  , 12) == 0)     my.delay   =   5;
      else if (strncmp (a, "--leisurely" , 12) == 0)     my.delay   =  15;
      else if (strncmp (a, "--passive"   , 12) == 0)     my.delay   = 300;
      else    continue;
      /*---(done)------------------------*/
      ++n;
   }
   DEBUG_ARGS   yLOG_value   ("#args"     , n);
   DEBUG_ARGS   yLOG_value   ("my.delay"  , my.delay);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}


char         /*--> prepare for program execution ---------[ leaf   [ ------ ]-*/
PROG_begin         (void)
{
   /*---(locals)-----------+-------------*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(daemonize)-----------------------------*/
   rc = yEXEC_daemon (yURG_debug.logger, &my.pid);
   DEBUG_TOPS   yLOG_value   ("daemonize" , rc);
   --rce;  if (rc < 0) {
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(setup signals)-------------------------*/
   DEBUG_TOPS   yLOG_note    ("signals set to bullet-proof (dangerous)");
   rc = yEXEC_signal (YEXEC_HARD, YEXEC_YES, YEXEC_YES, PROG_signal);
   DEBUG_TOPS   yLOG_value   ("signals"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> prepare interactive environment -------[ leaf   [ ------ ]-*/
PROG_final              (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}




/*====================------------------------------------====================*/
/*===----                          main driver                         ----===*/
/*====================------------------------------------====================*/

char sweep (void);

void             /* [------] receive signals ---------------------------------*/
PROG_signal        (int a_signal, siginfo_t *a_info, void *a_nada)
{
   switch (a_signal) {
   case  SIGHUP:
      yLOG_info  ("SIGNAL", "Local SIGHUP means refresh daemon");
      break;
   case  SIGUSR2:
      yLOG_info  ("SIGNAL", "Local SIGUSR2 means exec new version of kharon");
      /*> yEXEC_exec (EXEC_FILE, "restart_kharon", "root", "/sbin/kharon", yEXEC_BASH, yEXEC_NORM);   <*/
      break;
   }
   /*---(complete)-----------------------*/
   return;
}

char         /*--: wrapup program execution --------------[ leaf   [ ------ ]-*/
PROG_end           (void)
{
   /*---(create utmp boot)----------------------*/
   yLOG_enter (__FUNCTION__);
   yLOG_exit  (__FUNCTION__);
   yLOG_end   ();
   return 0;
}
