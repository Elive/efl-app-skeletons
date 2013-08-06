#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */

#include "elm_skel.h"

EAPI_MAIN int
elm_main(int argc EINA_UNUSED, char **argv EINA_UNUSED)
{
   printf("%s %s:\n  bin: %s\n  lib: %s\n data: %s\nsays %s\n",
          PACKAGE_NAME,
          VERSION,
          PACKAGE_BIN_DIR,
          PACKAGE_LIB_DIR,
          PACKAGE_DATA_DIR,
          elm_skel_hello());

   return EXIT_SUCCESS;
}

ELM_MAIN()

