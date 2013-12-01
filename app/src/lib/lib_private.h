#ifndef _MY_APP_LIB_PRIVATE_H
#define _MY_APP_LIB_PRIVATE_H

#include <Eina.h>

extern int _my_app_lib_log_dom;

#ifdef CRITICAL
#undef CRITICAL
#endif
#define CRITICAL(...) EINA_LOG_DOM_CRIT(_my_app_lib_log_dom, __VA_ARGS__)

#ifdef ERR
#undef ERR
#endif
#define ERR(...) EINA_LOG_DOM_ERR(_my_app_lib_log_dom, __VA_ARGS__)

#ifdef WRN
#undef WRN
#endif
#define WRN(...) EINA_LOG_DOM_WARN(_my_app_lib_log_dom, __VA_ARGS__)

#ifdef INF
#undef INF
#endif
#define INF(...) EINA_LOG_DOM_INFO(_my_app_lib_log_dom, __VA_ARGS__)

#ifdef DBG
#undef DBG
#endif
#define DBG(...) EINA_LOG_DOM_DBG(_my_app_lib_log_dom, __VA_ARGS__)

#endif   /* _MY_APP_LIB_PRIVATE_H */
