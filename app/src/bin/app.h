#ifndef _MY_APP_APP_H
#define _MY_APP_APP_H

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */

#include <Elementary.h>

#define MAX_PATH 64

extern int _my_app_log_dom;
#undef EINA_LOG_DOMAIN_DEFAULT
#define EINA_LOG_DOMAIN_DEFAULT _my_app_log_dom

#ifdef CRITICAL
#undef CRITICAL
#endif
#define CRITICAL(...) EINA_LOG_DOM_CRIT(_my_app_log_dom, __VA_ARGS__)

#ifdef ERR
#undef ERR
#endif
#define ERR(...) EINA_LOG_DOM_ERR(_my_app_log_dom, __VA_ARGS__)

#ifdef WRN
#undef WRN
#endif
#define WRN(...) EINA_LOG_DOM_WARN(_my_app_log_dom, __VA_ARGS__)

#ifdef INF
#undef INF
#endif
#define INF(...) EINA_LOG_DOM_INFO(_my_app_log_dom, __VA_ARGS__)

#ifdef DBG
#undef DBG
#endif
#define DBG(...) EINA_LOG_DOM_DBG(_my_app_log_dom, __VA_ARGS__)

typedef enum _App_Frames
{
   FRAME_MAIN = 0,
   FRAME_TUNNEL,
   MAX_FRAMES
} App_Frame;

typedef struct _Gui_Frame
{
   const char *name;
   Evas_Smart_Cb create_cb;
   Elm_Naviframe_Item_Pop_Cb pop_cb;
   Elm_Object_Item_Signal_Cb update_cb;
} Gui_Frame;

typedef struct _app {
   Eina_Bool      init_done;
   const char     *theme_path;
   const char     *extension_path;
   struct {
        Evas_Object  *win;
        Evas_Object  *popup;
        Evas_Object  *nf;
        Gui_Frame     frames[MAX_FRAMES];
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


/* APP GUI */

Evas_Object*
app_gui_create(App *app, Eina_Bool fullscreen, Eina_Rectangle geometry);

void
app_gui_notify(App *app, const char *msg);

void
app_gui_error(App *app, const char *msg);

#endif   /* _MY_APP_APP_H */
