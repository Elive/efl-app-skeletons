#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */

#include "Lib.h"
#include "lib_private.h"

int _elm_skel_lib_log_dom = -1;
int _elm_skel_lib_init_count = 0;

EAPI int
elm_skel_lib_init(void)
{
   const char * log_dom = "elm_skel_lib";

   if (++_elm_skel_lib_init_count != 1)
     {
        DBG("init count is %d.", _elm_skel_lib_init_count);
        return _elm_skel_lib_init_count;
     }

   if(!eina_init())
     goto shutdown_eina;

   _elm_skel_lib_log_dom = eina_log_domain_register(log_dom, EINA_COLOR_LIGHTBLUE);
   if (_elm_skel_lib_log_dom < 0)
     {
        EINA_LOG_ERR("Could not register log domain: %s", log_dom);
        goto shutdown_log_dom;
     }

   /* FIXME init stuff goes here */
   DBG("init...");

   return _elm_skel_lib_init_count;

shutdown_log_dom:
   eina_shutdown();
shutdown_eina:
   return --_elm_skel_lib_init_count;
}

EAPI int
elm_skel_lib_shutdown(void)
{
   if (_elm_skel_lib_init_count <= 0)
     {
        ERR("init count not greater than 0.");
        return 0;
     }

   if (--_elm_skel_lib_init_count != 0)
     {
        DBG("init count is %d.", _elm_skel_lib_init_count);
        return _elm_skel_lib_init_count;
     }

   /* FIXME shutdown stuff goes here */
   DBG("shutdown...");

   eina_shutdown();

   return _elm_skel_lib_init_count;
}

EAPI const char *
elm_skel_lib_hello(void)
{
   INF("called");
   return "Hello from the EFL world";
}

