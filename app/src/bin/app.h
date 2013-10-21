#ifndef _ELM_SKEL_APP_H
#define _ELM_SKEL_APP_H

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */

#include <Elementary.h>

#define MAX_PATH 64

extern int _elm_skel_log_dom;
#undef EINA_LOG_DOMAIN_DEFAULT
#define EINA_LOG_DOMAIN_DEFAULT _elm_skel_log_dom

#ifdef CRITICAL
#undef CRITICAL
#endif
#define CRITICAL(...) EINA_LOG_DOM_CRIT(_elm_skel_log_dom, __VA_ARGS__)

#ifdef ERR
#undef ERR
#endif
#define ERR(...) EINA_LOG_DOM_ERR(_elm_skel_log_dom, __VA_ARGS__)

#ifdef WRN
#undef WRN
#endif
#define WRN(...) EINA_LOG_DOM_WARN(_elm_skel_log_dom, __VA_ARGS__)

#ifdef INF
#undef INF
#endif
#define INF(...) EINA_LOG_DOM_INFO(_elm_skel_log_dom, __VA_ARGS__)

#ifdef DBG
#undef DBG
#endif
#define DBG(...) EINA_LOG_DOM_DBG(_elm_skel_log_dom, __VA_ARGS__)

typedef struct _app {
     Evas_Object  *win;
     Evas_Object  *nf;
     Evas_Object  *notify;
     Evas_Object  *popup;
     Eina_Bool    init_done;
     const char   *edje_path;
} App;

Evas_Object*
gui_create(Eina_Bool fullscreen, Eina_Rectangle geometry, const char* theme);

Eina_Bool
app_init(void);

void
app_shutdown(void);

void
app_notify(App *app, const char *msg);

void
app_popup(App *app, const char *msg);

#endif   /* _ELM_SKEL_APP_H */
