/*============================[[    beg-code    ]]============================*/
#include      "kharon.h"


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
