/*============================[[    beg-code    ]]============================*/
#include      "kharon.h"



tACCESSOR   my;



/*====================------------------------------------====================*/
/*===----                         support functions                    ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

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

char
PROG_vershow       (void)
{
   printf ("%s\n", PROG_version ());
   exit (0);
}

char             /* [------] display usage help information ------------------*/
PROG_about         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        t           [LEN_RECD];
   int         x_len       =    0;
   /*---(display)----------+-----+-----+-*/
   printf("\n");
   printf("focus     : %s\n", P_FOCUS);
   printf("niche     : %s\n", P_NICHE);
   printf("purpose   : %s\n", P_PURPOSE);
   printf("\n");
   printf("namesake  : %s\n", P_NAMESAKE);
   printf("heritage  : %s\n", P_HERITAGE);
   printf("imagery   : %s\n", P_IMAGERY);
   printf("\n");
   printf("system    : %s\n", P_SYSTEM);
   printf("language  : %s\n", P_LANGUAGE);
   printf("codesize  : %s\n", P_CODESIZE);
   printf("\n");
   printf("author    : %s\n", P_AUTHOR);
   printf("created   : %s\n", P_CREATED);
   printf("depends   : %s\n", P_DEPENDS);
   printf("\n");
   printf("ver num   : %s\n", P_VERNUM);
   printf("ver txt   : %s\n", P_VERTXT);
   printf("\n");
   strcpy (t, P_SUMMARY);
   x_len = strlen (t);
   for (i = 0; i < x_len; ++i)   if (t [i] == '¦')  t [i] = '\n';
   printf ("%s\n", t);
   printf("priority  : %s\n", P_PRIORITY);
   printf("principal : %s\n", P_PRINCIPAL);
   printf("reminder  : %s\n", P_REMINDER);
   printf("\n");
   printf("simplifying assumptions\n");
   strcpy (t, P_ASSUME);
   x_len = strlen (t);
   for (i = 0; i < x_len; ++i)   if (t [i] == '¦')  t [i] = '\n';
   printf ("%s\n", t);
   printf("\n");
   exit (0);
}



/*====================------------------------------------====================*/
/*===----                        program startup                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

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
      if      (strcmp (a, "--version"     ) == 0)   PROG_vershow ();
      else if (strcmp (a, "--about"       ) == 0)   PROG_about   ();
      else if (strcmp (a, "--rapid"       ) == 0)   my.delay   =   1;
      else if (strcmp (a, "--moderate"    ) == 0)   my.delay   =   5;
      else if (strcmp (a, "--leisurely"   ) == 0)   my.delay   =  15;
      else if (strcmp (a, "--passive"     ) == 0)   my.delay   = 300;
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

char         /*--> prepare visual/interactive env --------[ leaf   [ ------ ]-*/
PROG_visual             (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       specialty functions                    ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;}

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

char         /*--> daemonize the program -------------------------------------*/
PROG_daemon        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   int         x_running   =    0;
   int         x_uid       =    0;
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(check for other)----------------*/
   x_running = yEXEC_find ("kharon", NULL);
   DEBUG_ENVI   yLOG_value   ("x_running" , x_running);
   --rce;  if (x_running > 1) {
      printf ("already running in daemon mode\n");
      DEBUG_ENVI   yLOG_note    ("already running in daemon mode");
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for user)-----------------*/
   DEBUG_ENVI   yLOG_value   ("my.uid"    , my.uid);
   --rce;  if (my.uid != 0) {
      printf ("only root can run in daemon mode\n");
      DEBUG_ENVI   yLOG_note    ("only root can run in daemon mode");
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(fork off and die)---------------*/
   DEBUG_ENVI   yLOG_value   ("logger"    , yURG_lognum ());
   rc = yEXEC_daemon (yURG_lognum (), &my.pid);
   DEBUG_ENVI   yLOG_value   ("daemon"    , rc);
   --rce;  if (rc < 0) {
      printf ("could not be daemonized\n");
      DEBUG_ENVI   yLOG_note    ("could not be daemonized");
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(signals)-------------------------------*/
   rc = yEXEC_signal (YEXEC_HARD, YEXEC_NO, YEXEC_NO, PROG_signal);
   DEBUG_ENVI   yLOG_value   ("signals"   , rc);
   --rce;  if (rc < 0) {
      printf ("sigals could not be set properly\n");
      DEBUG_ENVI   yLOG_note    ("signals cound not be set properly");
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)------------------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN________________o (void) {;}

char         /*--: wrapup program execution --------------[ leaf   [ ------ ]-*/
PROG_end           (void)
{
   /*---(create utmp boot)----------------------*/
   yLOG_enter (__FUNCTION__);
   yLOG_exit  (__FUNCTION__);
   yLOG_end   ();
   return 0;
}
