#include <Elementary.h>
#include "config.h"

EAPI_MAIN int
elm_main(int argc EINA_UNUSED, char **argv EINA_UNUSED)
{
   printf("%s %s:\n  bin: %s\n  lib: %s\n data: %s\n",
          PACKAGE_NAME,
          VERSION,
          PACKAGE_BIN_DIR,
          PACKAGE_LIB_DIR,
          PACKAGE_DATA_DIR);

   return EXIT_SUCCESS;
}

ELM_MAIN()

