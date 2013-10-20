#ifndef _ELM_SKEL_LIB_PRIVATE_H
#define _ELM_SKEL_LIB_PRIVATE_H

#include <Eina.h>

extern int _elm_skel_lib_log_dom;

#ifdef CRITICAL
#undef CRITICAL
#endif
#define CRITICAL(...) EINA_LOG_DOM_CRIT(_elm_skel_lib_log_dom, __VA_ARGS__)

#ifdef ERR
#undef ERR
#endif
#define ERR(...) EINA_LOG_DOM_ERR(_elm_skel_lib_log_dom, __VA_ARGS__)

#ifdef WRN
#undef WRN
#endif
#define WRN(...) EINA_LOG_DOM_WARN(_elm_skel_lib_log_dom, __VA_ARGS__)

#ifdef INF
#undef INF
#endif
#define INF(...) EINA_LOG_DOM_INFO(_elm_skel_lib_log_dom, __VA_ARGS__)

#ifdef DBG
#undef DBG
#endif
#define DBG(...) EINA_LOG_DOM_DBG(_elm_skel_lib_log_dom, __VA_ARGS__)

#endif   /* _ELM_SKEL_LIB_PRIVATE_H */
