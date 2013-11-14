#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */

#include <Ecore_Getopt.h>

#include "app.h"

int _elm_skel_log_dom = -1;

static const Ecore_Getopt options =
{
   PACKAGE_NAME,
   "%prog [options]",
   VERSION,
   "(C) 2013 Jérémy Zurcher",
   "this code is … ASIS",
   "This is an skeleton for any efl/elm based application",
   1,
   {
      ECORE_GETOPT_LICENSE('L', "license"),
      ECORE_GETOPT_COPYRIGHT('C', "copyright"),
      ECORE_GETOPT_VERSION('V', "version"),
      ECORE_GETOPT_HELP('h', "help"),
      ECORE_GETOPT_CALLBACK_NOARGS('E', "list-engines",
                                   "list ecore-evas engines",
                                   ecore_getopt_callback_ecore_evas_list_engines,
                                   NULL),
      ECORE_GETOPT_STORE_TRUE('f', "fullscreen", "set f"),
      ECORE_GETOPT_CALLBACK_ARGS('g', "geometry",
                                 "geometry to use in x:y:w:h form.",
                                 "X:Y:W:H",
                                 ecore_getopt_callback_geometry_parse,
                                 NULL),
      ECORE_GETOPT_COUNT('v', "verbose",
                         "increase log verbosity"),
      ECORE_GETOPT_STORE_STR('e', "engine",
                             "ecore-evas engine to use"),
      ECORE_GETOPT_STORE_STR('t', "theme",
                             "edje theme application to use"),
      ECORE_GETOPT_SENTINEL
   }
};


EAPI_MAIN int
elm_main(int argc, char *argv[])
{
   App *app;

   char theme_file_path[MAX_PATH];
   char extension_file_path[MAX_PATH];
   Eina_Bool exit = EINA_FALSE;
   int args;
   char *theme = "default";
   char *engine = NULL;
   int verbosity = 0;
   Eina_Bool fullscreen = EINA_FALSE;
   Eina_Rectangle geometry = {600, 300, 300, 200};
   int eina_log_level = EINA_LOG_LEVEL_WARN;

   Ecore_Getopt_Value values[] =
     {
        ECORE_GETOPT_VALUE_BOOL(exit),
        ECORE_GETOPT_VALUE_BOOL(exit),
        ECORE_GETOPT_VALUE_BOOL(exit),
        ECORE_GETOPT_VALUE_BOOL(exit),
        ECORE_GETOPT_VALUE_BOOL(exit),
        ECORE_GETOPT_VALUE_BOOL(fullscreen),
        ECORE_GETOPT_VALUE_PTR_CAST(geometry),
        ECORE_GETOPT_VALUE_INT(verbosity),
        ECORE_GETOPT_VALUE_STR(engine),
        ECORE_GETOPT_VALUE_STR(theme),
        ECORE_GETOPT_VALUE_NONE
     };

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_app_compile_bin_dir_set(PACKAGE_BIN_DIR);
   elm_app_compile_lib_dir_set(PACKAGE_LIB_DIR);
   elm_app_compile_data_dir_set(PACKAGE_DATA_DIR);
   elm_app_info_set(elm_main, "elm_skel", "themes/default.edj");

   args = ecore_getopt_parse(&options, values, argc, argv);

   if (args < 0)
     {
        fprintf(stderr, "ERROR: could not parse command line options.\n");
        return EXIT_FAILURE;
     }

   if (exit) return EXIT_SUCCESS;

   eina_log_level += verbosity;
   if (eina_log_level > EINA_LOG_LEVEL_DBG)
     eina_log_level = EINA_LOG_LEVEL_DBG;
   eina_log_level_set(eina_log_level);

   if (engine) elm_config_preferred_engine_set(engine);

   eina_log_color_disable_set(EINA_FALSE);
   _elm_skel_log_dom = eina_log_domain_register(PACKAGE_NAME, EINA_COLOR_CYAN);

   EINA_LOG_DOM_INFO(_elm_skel_log_dom, "%s %s:", PACKAGE_NAME, VERSION);
   EINA_LOG_DOM_DBG(_elm_skel_log_dom, "\n  bin: %s\n  lib: %s\n data: %s",
                elm_app_bin_dir_get(),
                elm_app_lib_dir_get(),
                elm_app_data_dir_get());

   snprintf(theme_file_path, MAX_PATH, "%s/themes/%s.edj",
            elm_app_data_dir_get(), theme);
   snprintf(extension_file_path, MAX_PATH, "%s/themes/%s-ext.edj",
            elm_app_data_dir_get(), theme);

   app = app_get(theme_file_path, extension_file_path);
   if (!gui_create(app, fullscreen, geometry))
     {
        EINA_LOG_DOM_ERR(_elm_skel_log_dom, "unable to create application window");
        app_free(app);
        return EXIT_FAILURE;
     }

   app_init(app);

   elm_run();

   app_shutdown(app);
   elm_shutdown();

   app_free(app);

   return EXIT_SUCCESS;
}

ELM_MAIN()

