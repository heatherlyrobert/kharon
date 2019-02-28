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

#define     P_VERNUM    "2.0b"
#define     P_VERTXT    "added standard prog functions and debugging protection"


/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/



/*===[[ SUMMARY ]]============================================================*/
/* 
 *   eos is intended to be a clean, reliable, and light system initialization
 *   process to receive the hand off from the kernel and deliver a stable,
 *   secure, and well prepared system for use to kharon who will watch over
 *   the system while it is running.
 */



/*===[[ SUMMARY ]]============================================================*/
/*
 *   kharon is a very focused element of the init system who's only purpose is
 *   to ferry dead processes and zombies out of the running system.  kharon is
 *   started by eos (rosy-fingered dawn) and then turns over control to
 *   astraeus (dusk, dawn of stars) at system shutdown.
 *
 */

/*===[[ DESIGN GOALS ]]=======================================================*/
/*
 *   kharon has a very specific, focused domai and it MUST stay functioning.
 *   so, it will require...
 *      -- very simple coding
 *      -- no input or configuration files
 *      -- all libraries are staticly linked
 *      -- no options
 *      -- very limited requirements and dependencies
 *      -- very limited security access
 *      -- will never run or launch anything
 *      -- kharon ALWAYS logs
 *
 */

/*===[[ MYTHOS ]]=============================================================*/
/*
 *   kharon is the ferryman of hades who carries souls of the newly deceased
 *   across the river acheron (pain/sorrow) which is one of the five rivers of
 *   hell with the styx (hate/oath), lethe (oblivion/forgetfulness),
 *   phlegethon (fire/blood), and cocytus (wailing/lamentation) that divided the
 *   world of the living from the world of the dead.
 *
 *   kharon is the son of erebus (darkness) and nyx (night).
 *
 *   kharon continues in modern folklore as the angel of death.
 *
 *   pronounced as "k-air-ahn"
 *
 */
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

typedef  struct cACCESSOR tACCESSOR;
struct cACCESSOR
{
   char        version       [500];         /* program version string         */
   int         delay;                       /* delay in seconds               */
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

typedef struct FILE      tFILE;
typedef struct stat      tSTAT;
typedef struct passwd    tPASSWD;
typedef struct group     tGROUP;
typedef struct rusage    tRUSAGE;
typedef struct tm        tTIME;
typedef struct dirent    tDIRENT;




/*---(program)--------------*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char*       PROG_version            (void);
char        PROG_preinit            (void);
char        PROG_init               (void);
char        PROG_args               (int a_argc, char *a_argv[]);
char        PROG_begin              (void);
char        PROG_final              (void);
void        PROG_signal             (int a_signal, siginfo_t *a_info, void *a_nada);
char        PROG_end                (void);


#endif
/*============================[[ end-of-code ]]===============================*/
