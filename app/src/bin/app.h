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
   Eina_Bool      init_done;
   const char     *theme_path;
   const char     *extension_path;
   struct {
        Evas_Object  *win;
        Evas_Object  *popup;
        Evas_Object  *notify;
        Evas_Object  *nf;
   } gui;
} App;


/* APP */

App *
app_get(const char *theme_path, const char *extension_path);

void
app_free(App *app);

Eina_Bool
app_init(App *app);

void
app_shutdown(App *app);

/* GUI */
Evas_Object*
gui_create(App *app, Eina_Bool fullscreen, Eina_Rectangle geometry);

void
app_notify(App *app, const char *msg);

void
app_popup(App *app, const char *msg);

#endif   /* _ELM_SKEL_APP_H */
