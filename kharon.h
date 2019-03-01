/*============================[[ beg-of-code ]]===============================*/

/*===[[ HEADER ]]=============================================================*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_FOCUS     "SA (system administration)"
#define     P_NICHE     "rt (process one run-time)"
#define     P_PURPOSE   "consistent, reliable handling of terminated processes"

#define     P_NAMESAKE  "kharon-daimon (ferryman of the dead)"
#define     P_HERITAGE  "haides ferryman, carrying the dead across the rivers of hell"
#define     P_IMAGERY   "ugly, bearded man in a conical hat, polling a black skiff"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2010-10"
#define     P_DEPENDS   "yEXEC, ySTR"

#define     P_VERNUM    "2.0d"
#define     P_VERTXT    "cleaned up and unit tested PROG_args setting"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "i know there are many better options, but i *own* this one"

#define     P_GREEK     \
 "kharon (k-air-ahn) is the ferryman of haides who carries souls of the newly¦" \
 "deceased across the river acheron (pain/sorrow) which is one of the five¦" \
 "rivers of hell -- styx (hate/oath), lethe (oblivion/forgetfulness),¦" \
 "phlegethon (fire/blood), and cocytus (wailing/lamentation) -- that divided the¦" \
 "world of the living from the world of the dead.  kharon is the son of erebus¦" \
 "(darkness) and nyx (night).  kharon continues in modern folklore as the¦" \
 "angel of death.¦"

/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_SUMMARY   \
 "kharon is a very specialized part of the init process, which handles¦" \
 "the collection of completed, killed, dead, and zombie processes during¦" \
 "normal operation of the system.¦"
#define     P_CURRENT   \
 "there are a number of competing init systems which cover a wide range of¦" \
 "capabilities -- startup, shutdown, resurrection, collection, and in some¦" \
 "cases event, resource, and time-based launching of processes.¦"
#define     P_ALTERNS   "sysvinit,openrc,systemd,upstart,runit,minirc,minit"
#define     P_CONCERN   \
 "init has evolved into a kitchen-sink and gone beyond mere mortals to¦" \
 "maintain and control requiring secondard packages of macros, scripts,¦" \
 "and configuration.  the economies of scale argument always ends in a mess.¦"
#define     P_USERBASE  \
 "never confuse tailored, technical, super-user systems and general, easy-¦" \
 "to-use, zero effort required systems built to get end-users up and happy¦" \
 "as quickly as possible.¦"
#define     P_COURSE    \
 "no way.  this is not the unix way of focused, narrow processes linked to¦" \
 "handle complex situations.  i will break init into startup, shutdown,¦" \
 "run-time, ressurection, and leave cron separate.¦"
#define     P_ASSUME    \
 "-- all init startup operations handled by eos (rosy-fingered dawn)¦" \
 "-- all init shutdown operations handled by astraios (dusk, dawn of stars)¦" \
 "-- all init resurrection (serial) operations handled by haides¦" \
 "-- zero configuration and limited command line options¦" \
 "-- will never run or launch any processes or need serious security access¦" \
 "-- communication of state changes through signals, not fifo or pipe¦"


/*===[[ BACKGROUD ]]==========================================================*/

/*   this element of the init system (post startup) normally handles several
 *   critical responsibilities...
 *      - retire dead processes
 *      - sweep up zombies
 *      - restart specific processes, such as gettys
 *      - manage changes to the runlevel
 *
 *   in our init system the first two are kharon, but the third is joined with
 *   the larger role of system watchdog given to haides, and the last is also
 *   given to another process.  so, kharon is left with a very, very lean and
 *   focused role -- better for security and reliability.
 *
 */
/*============================================================================*/



/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YKHARON
#define YKHARON loaded



/*===[[ VERSIONING ]]=========================================================*/
/* rapidly evolving version number to aid with visual change confirmation     */
#define     YKHARON_VER_NUM   "2.0a"
#define     YKHARON_VER_TXT   "breakout from initd source tree"



/*===[[ PRIVATE HEADERS ]]====================================================*/
#include    <yEXEC.h>             /* heatherly process control                */
#include    <ySTR.h>              /* heatherly safe string library            */
#include    <yURG.h>              /* heatherly debugging framework            */
#include    <yLOG.h>              /* heatherly logger                         */


/*===[[ PUBLIC HEADERS ]]=====================================================*/
/*---(big standards)------------*/
#include    <stdio.h>             /* printf, scanf                            */
#include    <stdlib.h>            /* exit, system, ...                        */
#include    <sys/unistd.h>        /* fork, execl, getpid, getuid              */
#include    <string.h>            /* strcat, strcpy, strlen, ...              */

/*---(process)------------------*/
#include    <sys/wait.h>          /* sigaction, waitpid, wait4                */
#include    <sys/time.h>          /* getrusage                                */
#include    <sys/resource.h>      /* getrusage                                */
#include    <errno.h>             /* errno                                    */

/*---(timekeeping)--------------*/
#include    <time.h>              /* time, localtime, strftime, ...           */
#include    <sys/time.h>          /* gettimeofday                             */

/*---(filesystems)--------------*/
#include    <sys/mount.h>         /* mount                                    */
#include    <fcntl.h>             /* open                                     */
#include    <sys/stat.h>          /* fstat, umask                             */
#include    <dirent.h>

/*---(users)--------------------*/
#include    <pwd.h>               /* getpwuid, getpwnam                       */
#include    <grp.h>               /* initgroups                               */

/*---(user tracking)------------*/
#include    <utmp.h>              /* utmp, btmp, and wtmp tracking            */

/*---(structures)-----------------------------------------------*/
typedef struct stat      tSTAT;



/*---(run_mode)---------------------------------*/
#define     MODE_VERIFY      'v'            /* verification and review        */
#define     MODE_DAEMON      'd'            /* normal daemon (default)        */
#define     MODE_CONTROL     'c'            /* send messages to the daemon    */
#define     MODE_UNIT        'u'            /* unit testing settings          */
#define     MODE_VALID       "vdcu"

/*---(actions)----------------------------------*/
#define     ACT_NONE         '-'            /* no action                      */
#define     ACT_NEWCODE      'n'            /* update with new version        */
#define     ACT_DEBUG        'd'            /* switch to debug version        */
#define     ACT_PROD         'p'            /* switch to production/clean     */
#define     ACT_SHUTDOWN     's'            /* switch to astreios/shutdown    */
#define     ACT_VALID        "-ndps"

#define     FILE_HEARTBEAT   "/run/kharon.heartbeat"


typedef  struct cACCESSOR tACCESSOR;
struct cACCESSOR
{
   /*---(behavior)-------------*/
   char        run_desc      [LEN_LABEL];   /* mode description               */
   char        run_mode;                    /* user, daemon, control, unit    */
   char        speed         [LEN_LABEL];   /* speed/pace of checks           */
   int         delay;                       /* delay in seconds               */
   char        river         [LEN_LABEL];   /* river of hell                  */
   char        act_desc      [LEN_LABEL];   /* action description             */
   char        act_code;                    /* action code                    */
   /*---(master)---------------*/
   char        heartbeat     [LEN_HUND];    /* heartbeat string               */
   char       *cmdline;                     /* system command line position   */
   int         maxname;                     /* maximum command line size      */
   char        version       [500];         /* program version string         */
   /*---(owner)----------------*/
   int         pid;                         /* process id of eos              */
   int         ppid;                        /* parent process id of eos       */
   int         uid;                         /* uid of person who launched eos */
   char        who         [LEN_LABEL];     /* user name who launched eos     */
   /*---(files)----------------*/
   int         logger;                      /* log file                       */
   char        updates;                     /* bool : 0=normal, 1=quiet       */
};
extern      tACCESSOR   my;


#define     EXEC_FILE        "/var/log/yLOG/kharon_exec" 
#define     UTMP             "/var/run/utmp"
#define     WTMP             "/var/log/wtmp"
#define     BTMP             "/var/log/btmp"
#define     SULOG            "/var/log/sulog"
#define     LASTLOG          "/var/log/lastlog"
#define     PASSWD           "/etc/passwd"
#define     SHADOW           "/etc/shadow"
#define     GROUP            "/etc/group"
#define     GSHADOW          "/etc/gshadow"
#define     TTY              "/etc/securetty"
#define     HESTIA           "/var/log/hestia.logging"

#define     LOGIN            "/etc/login.defs"
#define     NOLOGIN          "/etc/nologin"
#define     LIMITS           "/etc/limits"
#define     USERTTY          "/etc/usertty"

#define     LOGGER           if (my.logger >= 1)

/*---(convienence typedefs)-------------------------------------*/
typedef long   long      llong;
typedef const  int       cint;
typedef const  long      clong;
typedef const  char      cchar;

typedef struct rusage    tRUSAGE;
typedef struct dirent    tDIRENT;


extern      char        unit_answer [LEN_RECD];


/*---(program)--------------*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(support)-----------------*/
char*       PROG_version            (void);
char        PROG_vershow            (void);
char        PROG_about              (void);
/*---(startup)-----------------*/
char        PROG_init               (int a_argc, char *a_argv []);
char        PROG_args               (int a_argc, char *a_argv[]);
/*---(specialty)---------------*/
void        PROG_signal             (int a_signal, siginfo_t *a_info, void *a_nada);
char        PROG_daemon             (void);
/*---(shutdown)----------------*/
char        PROG_end                (void);
/*---(unit test)---------------*/
char*       prog__unit              (char *a_question, int a_num);
char        prog__unit_quiet        (void);
char        prog__unit_loud         (void);
char        prog__unit_end          (void);

char        exec_mode               (char *a_name, char a_mode);
char        exec_action             (char *a_name, char a_act);
char        exec_speed              (char *a_name, int a_speed);
char        exec_river              (char *a_name);
char        exec_retitle            (void);

char        fifo_verify             (void);
char        fifo_listen             (void);
char        fifo_speak              (void);


#endif
/*============================[[ end-of-code ]]===============================*/
