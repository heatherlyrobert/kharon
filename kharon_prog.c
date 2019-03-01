/*============================[[    beg-code    ]]============================*/
#include      "kharon.h"



tACCESSOR   my;
char        unit_answer [LEN_RECD];



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
   printf("major simplifying assumptions...\n");
   strcpy (t, P_ASSUME);
   x_len = strlen (t);
   for (i = 0; i < x_len; ++i)   if (t [i] == '¦')  t [i] = '\n';
   printf ("%s\n", t);
   printf("__________________________expanded greek background__________________________\n");
   strcpy (t, P_GREEK);
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

char         /*--> pre-argument processing ---------------[ leaf   [ ------ ]-*/
PROG_init               (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-------------*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(begin)--------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_info    ("namesake", P_NAMESAKE);
   DEBUG_TOPS   yLOG_info    ("heritage", P_HERITAGE);
   DEBUG_TOPS   yLOG_info    ("imagery" , P_IMAGERY);
   DEBUG_TOPS   yLOG_info    ("purpose" , P_PURPOSE);
   DEBUG_TOPS   yLOG_info    ("kharon"  , PROG_version  ());
   DEBUG_TOPS   yLOG_info    ("yEXEC"   , yEXEC_version ());
   DEBUG_TOPS   yLOG_info    ("ySTR"    , ySTR_version  ());
   DEBUG_TOPS   yLOG_info    ("yURG"    , yURG_version  ());
   DEBUG_TOPS   yLOG_info    ("yLOG"    , yLOG_version  ());
   /*---(quick defaults)-----------------*/
   strlcpy (my.run_desc, "daemon"      , LEN_LABEL);
   my.run_mode       = MODE_DAEMON;
   /*---(call whoami)--------------------*/
   rc = yEXEC_whoami (&my.pid, &my.ppid, &my.uid, NULL, &my.who, 'n');
   DEBUG_PROG   yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_value   ("pid"       , my.pid);
   DEBUG_PROG   yLOG_value   ("ppid"      , my.ppid);
   DEBUG_PROG   yLOG_value   ("uid"       , my.uid);
   DEBUG_PROG   yLOG_info    ("who"       , my.who);
   /*---(defaults)-----------------------*/
   strlcpy (my.act_desc, ""          , LEN_LABEL);
   my.act_code = '-';
   strlcpy (my.speed, "leisurely"   , LEN_LABEL);
   my.delay    = 15;
   strlcpy (my.river, "acheron"     , LEN_LABEL);
   /*---(command line)-------------------*/
   my.cmdline = a_argv [0];
   DEBUG_PROG   yLOG_point   ("cmdline"   , my.cmdline);
   rc = yEXEC_maxname (a_argc, a_argv, &my.maxname);
   DEBUG_PROG   yLOG_value   ("maxname"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_value   ("maxname"   , my.maxname);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
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
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
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
      /*---(run modes)-------------------*/
      else if (strcmp (a, "--daemon"      ) == 0)   exec_mode  (a, MODE_DAEMON);
      else if (strcmp (a, "--control"     ) == 0)   exec_mode  (a, MODE_CONTROL);
      else if (strcmp (a, "--verify"      ) == 0)   exec_mode  (a, MODE_VERIFY);
      /*---(speed)-----------------------*/
      else if (strcmp (a, "--rapid"       ) == 0)   exec_speed (a,   1);
      else if (strcmp (a, "--moderate"    ) == 0)   exec_speed (a,   5);
      else if (strcmp (a, "--leisurely"   ) == 0)   exec_speed (a,  15);
      else if (strcmp (a, "--passive"     ) == 0)   exec_speed (a, 300);
      /*---(rivers of hell)-----------------*/
      else if (strcmp (a, "--acheron"     ) == 0)   exec_river (a); /* future (pain)        */
      else if (strcmp (a, "--styx"        ) == 0)   exec_river (a); /* future (hate)        */
      else if (strcmp (a, "--lethe"       ) == 0)   exec_river (a); /* future (oblivion)    */
      else if (strcmp (a, "--phlegethon"  ) == 0)   exec_river (a); /* future (blood)       */
      else if (strcmp (a, "--cocytus"     ) == 0)   exec_river (a); /* future (lamentation) */
      /*---(transition)-----------------*/
      else if (strcmp (a, "--shutdown"    ) == 0)   exec_action (a, ACT_SHUTDOWN);
      else if (strcmp (a, "--newcode"     ) == 0)   exec_action (a, ACT_NEWCODE);
      else if (strcmp (a, "--debug"       ) == 0)   exec_action (a, ACT_DEBUG);
      else if (strcmp (a, "--production"  ) == 0)   exec_action (a, ACT_PROD);
      /*---(done)------------------------*/
      ++n;
   }
   DEBUG_ARGS   yLOG_value   ("#args"     , n);
   DEBUG_ARGS   yLOG_info    ("run_desc"  , my.run_desc);
   DEBUG_ARGS   yLOG_char    ("run_mode"  , my.run_mode);
   DEBUG_ARGS   yLOG_info    ("act_desc"  , my.act_desc);
   DEBUG_ARGS   yLOG_char    ("act_code"  , my.act_code);
   DEBUG_ARGS   yLOG_info    ("speed"     , my.speed);
   DEBUG_ARGS   yLOG_value   ("delay"     , my.delay);
   DEBUG_ARGS   yLOG_info    ("river"     , my.river);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
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



/*====================------------------------------------====================*/
/*===----                      unit test accessor                      ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*            /*--> unit test accessor ------------------------------*/
prog__unit              (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_LABEL]  = "[]";
   /*---(prepare)------------------------*/
   strlcpy  (unit_answer, "PROG             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "mode"    )        == 0) {
      sprintf (t, "[%s]", my.run_desc);
      snprintf (unit_answer, LEN_RECD, "PROG mode        : %2d%-22.22s  %c", strlen (my.run_desc), t, my.run_mode);
   }
   else if (strcmp (a_question, "action"  )        == 0) {
      sprintf (t, "[%s]", my.act_desc);
      snprintf (unit_answer, LEN_RECD, "PROG action      : %2d%-22.22s  %c", strlen (my.act_desc), t, my.act_code);
   }
   else if (strcmp (a_question, "river"   )        == 0) {
      sprintf (t, "[%s]", my.river);
      snprintf (unit_answer, LEN_RECD, "PROG river       : %2d%s", strlen (my.river), t);
   }
   else if (strcmp (a_question, "speed"   )        == 0) {
      sprintf (t, "[%s]", my.speed);
      snprintf (unit_answer, LEN_RECD, "PROG speed       : %2d%-22.22s  %3d", strlen (my.speed), t, my.delay);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

char       /*----: set up program test file locations ------------------------*/
prog__unit_files   (void)
{
   /*> char        x_cmd       [LEN_RECD];                                            <* 
    *> chdir    ("/tmp");                                                             <* 
    *> sprintf  (x_cmd, "rm -fr %s* > /dev/null", DIR_UNIT);                          <* 
    *> system   (x_cmd);                                                              <* 
    *> rmdir    (DIR_UNIT);                                                           <* 
    *> sprintf  (x_cmd, "mkdir %s   > /dev/null", DIR_UNIT);                          <* 
    *> system   (x_cmd);                                                              <*/
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
prog__unit_quiet   (void)
{
   int         x_argc      = 1;
   char       *x_argv [1]  = { "kharon" };
   yURG_logger    (x_argc, x_argv);
   yURG_urgs      (x_argc, x_argv);
   PROG_init      (x_argc, x_argv);
   prog__unit_files ();
   PROG_args      (x_argc, x_argv);
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
prog__unit_loud    (void)
{
   int         x_argc      = 2;
   char       *x_argv [2]  = { "kharon_unit", "@@kitchen", "@@yexec"  };
   yURG_logger    (x_argc, x_argv);
   yURG_urgs      (x_argc, x_argv);
   PROG_init      (x_argc, x_argv);
   prog__unit_files ();
   PROG_args      (x_argc, x_argv);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
prog__unit_end     (void)
{
   char        x_cmd       [LEN_RECD];
   /*> chdir    ("/tmp");                                                             <* 
    *> sprintf  (x_cmd, "rm -fr %s* > /dev/null", DIR_UNIT);                          <* 
    *> system   (x_cmd);                                                              <* 
    *> rmdir    (DIR_UNIT);                                                           <*/
   PROG_end       ();
   return 0;
}




