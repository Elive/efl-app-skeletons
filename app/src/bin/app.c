#include "app.h"
#include "Lib.h"

/* MODULES */
static Eina_Bool
_module0_init(App *app EINA_UNUSED)
{
   return EINA_TRUE;
}

static void
_module0_shutdown(App *app EINA_UNUSED)
{
}

static Eina_Bool
_module1_init(App *app EINA_UNUSED)
{
   return EINA_TRUE;
}

static void
_module1_shutdown(App *app EINA_UNUSED)
{
}

/* APP API */
Eina_Bool
app_init(App *app)
{
   if (app->init_done)
     return EINA_TRUE;

   app_gui_notify(app, "Application initializing...");

   if(!elm_skel_lib_init())
     {
        app_gui_error(app, "initialization miserably failed.");
        goto shutdown_none;
     }

   if (!_module0_init(app))
     {
        app_gui_error(app, "unable to init module 0.");
        goto shutdown_skel_lib;
     }

   if (!_module1_init(app))
     {
        app_gui_error(app, "unable to init module 1.");
        goto shutdown_module0;
     }

   app->init_done = EINA_TRUE;

   return EINA_TRUE;

shutdown_skel_lib:
   elm_skel_lib_shutdown();
shutdown_module0:
   _module0_shutdown(app);
shutdown_none:
   return EINA_FALSE;
}

void
app_shutdown(App *app)
{
   if (app->init_done)
     {
        _module1_shutdown(app);
        _module0_shutdown(app);
        elm_skel_lib_shutdown();
     }

   app->init_done = EINA_FALSE;
}

App *
app_get(const char *theme_path, const char *extension_path)
{
   App *app = calloc(1, sizeof(App));

   app->init_done = EINA_FALSE;

   if (theme_path)
      app->theme_path = eina_stringshare_add(theme_path);
   if (extension_path)
      app->extension_path = eina_stringshare_add(extension_path);

   return app;
}

void
app_free(App *app)
{
   if (app->theme_path)
     eina_stringshare_del(app->theme_path);
   if (app->extension_path)
     eina_stringshare_del(app->extension_path);

   if (app->init_done)
     app_shutdown(app);

   free(app);
}

