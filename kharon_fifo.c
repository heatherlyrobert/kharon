/*============================[[    beg-code    ]]============================*/
#include      "kharon.h"



#define     KHARON_FIFO     "/run/kharon"


char         /*--> verify and create fifo ------------------------------------*/
fifo_verify             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tSTAT       s;
   /*---(header)-------------------------*/
   DEBUG_APIS   yLOG_enter   (__FUNCTION__);
   /*---(check existance)----------------*/
   rc = stat (KHARON_FIFO, &s);
   DEBUG_APIS   yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      /*---(create)----------------------*/
      rc = mkfifo (KHARON_FIFO, 0600);
      DEBUG_APIS   yLOG_value   ("mkfifo"    , rc);
      --rce;  if (rc < 0) {
         DEBUG_APIS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(re-check existance)----------*/
      rc = stat (KHARON_FIFO, &s);
      DEBUG_APIS   yLOG_value   ("re-stat"   , rc);
      --rce;  if (rc < 0) {
         DEBUG_APIS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(change ownership)---------------*/
   rc = chown (KHARON_FIFO, 0, 0);
   DEBUG_APIS   yLOG_value   ("chown"     , rc);
   --rce;  if (rc != 0) {
      DEBUG_APIS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check file type)----------------*/
   --rce;  if (S_ISDIR (s.st_mode))  {
      DEBUG_APIS   yLOG_note    ("can not use a directory");
      DEBUG_APIS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_APIS   yLOG_note    ("not a directory");
   --rce;  if (S_ISLNK (s.st_mode))  {
      DEBUG_APIS   yLOG_note    ("can not use a symlink");
      DEBUG_APIS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_APIS   yLOG_note    ("not a symlink");
   --rce;  if (S_ISCHR (s.st_mode))  {
      DEBUG_APIS   yLOG_note    ("can not use a character device");
      DEBUG_APIS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_APIS   yLOG_note    ("not a symlink");
   --rce;  if (!S_ISFIFO (s.st_mode))  {
      DEBUG_APIS   yLOG_note    ("can only use fifo/pipe files");
      DEBUG_APIS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_APIS   yLOG_note    ("confirmed as a fifo/pipe file");
   /*---(complete)-----------------------*/
   DEBUG_APIS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> gather run-time changes -----------------------------------*/
fifo_listen             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         x_fd        =   -1;
   char        x_action    [LEN_LABEL];
   int         x_delay     =    0;
   char        x_river     =  '-';
   /*---(header)-------------------------*/
   DEBUG_APIS   yLOG_enter   (__FUNCTION__);
   /*---(open fifo)----------------------*/
   rc = open (KHARON_FIFO, O_RDWR|O_NONBLOCK);
   DEBUG_APIS   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_APIS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read)---------------------------*/
   rc = read (x_fd, x_action, LEN_LABEL);
   DEBUG_APIS   yLOG_value   ("read"      , rc);
   if (rc <= 0) {
      DEBUG_APIS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(save)---------------------------*/
   x_delay   = my.delay;
   x_river   = my.river;
   my.act_code = '-';
   /*---(speed)--------------------------*/
   if      (strcmp (x_action, "--rapid"       ) == 0)   exec_speed (x_action,   1);
   else if (strcmp (x_action, "--moderate"    ) == 0)   exec_speed (x_action,   5);
   else if (strcmp (x_action, "--leisurely"   ) == 0)   exec_speed (x_action,  15);
   else if (strcmp (x_action, "--passive"     ) == 0)   exec_speed (x_action, 300);
   /*---(rivers of hell)-----------------*/
   else if (strcmp (x_action, "--acheron"     ) == 0)   exec_river (x_action); /* future (pain)        */
   else if (strcmp (x_action, "--styx"        ) == 0)   exec_river (x_action); /* future (hate)        */
   else if (strcmp (x_action, "--lethe"       ) == 0)   exec_river (x_action); /* future (oblivion)    */
   else if (strcmp (x_action, "--phlegethon"  ) == 0)   exec_river (x_action); /* future (blood)       */
   else if (strcmp (x_action, "--cocytus"     ) == 0)   exec_river (x_action); /* future (lamentation) */
   /*---(transitions)--------------------*/
   else if (strcmp (x_action, "--shutdown"    ) == 0)   my.act_code = 's'; /* call astraios        */
   else if (strcmp (x_action, "--update"      ) == 0)   my.act_code = 'u'; /* update version       */
   /*---(retitle)------------------------*/
   rc = exec_retitle ();
   /*---(complete)-----------------------*/
   DEBUG_APIS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
fifo_speak              (void)
{
}




