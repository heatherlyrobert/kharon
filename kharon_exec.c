/*============================[[    beg-code    ]]============================*/
#include      "kharon.h"




char
exec_mode               (char *a_name, char a_mode)
{
   /*---(header)-------------------------*/
   DEBUG_APIS   yLOG_senter  (__FUNCTION__);
   /*---(update)-------------------------*/
   strlcpy (my.run_desc, a_name + 2, LEN_LABEL);
   DEBUG_APIS   yLOG_snote   (my.run_desc);
   my.run_mode = a_mode;
   DEBUG_APIS   yLOG_sint    (my.run_mode);
   /*---(complete)-----------------------*/
   DEBUG_APIS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
exec_action             (char *a_name, char a_act)
{
   /*---(header)-------------------------*/
   DEBUG_APIS   yLOG_senter  (__FUNCTION__);
   /*---(update)-------------------------*/
   strlcpy (my.act_desc, a_name + 2, LEN_LABEL);
   DEBUG_APIS   yLOG_snote   (my.act_desc);
   my.act_code = a_act;
   DEBUG_APIS   yLOG_sint    (my.act_code);
   /*---(complete)-----------------------*/
   DEBUG_APIS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
exec_speed              (char *a_name, int a_speed)
{
   /*---(header)-------------------------*/
   DEBUG_APIS   yLOG_senter  (__FUNCTION__);
   /*---(update)-------------------------*/
   strlcpy (my.speed, a_name + 2, LEN_LABEL);
   DEBUG_APIS   yLOG_snote   (my.speed);
   my.delay = a_speed;
   DEBUG_APIS   yLOG_sint    (my.delay);
   /*---(complete)-----------------------*/
   DEBUG_APIS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
exec_river              (char *a_name)
{
   /*---(header)-------------------------*/
   DEBUG_APIS   yLOG_senter  (__FUNCTION__);
   /*---(update)-------------------------*/
   strlcpy (my.river, a_name + 2, LEN_LABEL);
   DEBUG_APIS   yLOG_snote   (my.river);
   /*---(complete)-----------------------*/
   DEBUG_APIS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
exec_retitle            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        t           [LEN_HUND];
   /*---(header)-------------------------*/
   DEBUG_APIS   yLOG_enter   (__FUNCTION__);
   /*---(update)-------------------------*/
   sprintf (t, "/sbin/kharon --%s --%s", my.river, my.speed);
   rc = yEXEC_rename (my.cmdline, t, my.maxname);
   /*---(complete)-----------------------*/
   DEBUG_APIS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /* PURPOSE : run through all processes ----------------------------*/
sweep              (void)
{
   /*---(locals)-----------+-----------+-*/
   tDIRENT    *den;
   DIR        *dir;
   FILE       *f;
   char        name        [1000];
   char        line        [1000];
   char        title       [1000];
   int         ppid        = 0;
   int         rc;
   char       *p;
   int         status;
   tRUSAGE     r_use;
   int         hestia;
   int         dead        = 0;
   char        rchar       = 0;
   /*---(open the proc system)-----------*/
   dir = opendir("/proc");
   if (dir == NULL) return -1;
   /*---(cycle through the entries)------*/
   while ((den = readdir(dir)) != NULL) {
      /*---(filter non-processes)--------*/
      if (atoi(den->d_name)   == 0)        continue;
      if (strlen(den->d_name) == 0)        continue;
      /*---(open process file)-----------*/
      snprintf(name, 900, "/proc/%s/stat", den->d_name);
      f = fopen(name, "r");
      if (f == NULL)                       continue;
      /*---(read the entry)--------------*/
      fgets (line,  900, f);
      /*---(parse title)-----------------*/
      p = strtok (line, "(");
      if (p == NULL)         { fclose (f); continue; }
      p = strtok (NULL, ")");
      if (p == NULL)         { fclose (f); continue; }
      if (strlen (p) == 0)   { fclose (f); continue; }
      strncpy (title, p, 900);
      /*---(parse ppid)------------------*/
      p = strtok (NULL, " ");
      if (p == NULL)         { fclose (f); continue; }
      p = strtok (NULL, " ");
      if (p == NULL)         { fclose (f); continue; }
      ppid = atoi (p);
      if (ppid == 0)         { fclose (f); continue; }
      /*---(close process file)----------*/
      fclose (f);
      /*---(check if kharon owns)--------*/
      if (ppid  != 1)                      continue;
      /*---(read the entry)--------------*/
      rc = getrusage (RUSAGE_SELF, &r_use);
      if (rc < 0)                          continue;
      rc = waitpid   (atoi (den->d_name), &status, WNOHANG);
      if (rc <= 0)                         continue;
      /*---(report)----------------------*/
      yLOG_senter ("collect");
      yLOG_svalue ("pid"     , (int) rc);
      yLOG_sinfo  ("ppid"    , p);
      yLOG_snote  (title);
      rchar = WEXITSTATUS (status);
      yLOG_svalue ("rc"      , (int) (rchar));
      yLOG_svalue ("utime"   , (int) ((r_use.ru_utime.tv_sec * 1000) + (r_use.ru_utime.tv_usec / 1000)));
      yLOG_svalue ("stime"   , (int) ((r_use.ru_stime.tv_sec * 1000) + (r_use.ru_stime.tv_usec / 1000)));
      yLOG_svalue ("switches", (int) r_use.ru_nvcsw + r_use.ru_nivcsw);
      yLOG_snote  ("done");
      yLOG_sexit  ("collect");
      /*---(prepare for next)------------*/
      ++dead;
   }
   /*---(close the dir)------------------*/
   closedir(dir);
   /*---(complete)-----------------------*/
   return 0;
}
