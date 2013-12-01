#ifndef _MY_APP_LIB_H
#define _MY_APP_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Eina.h>

/**
 * Initialize Lib
 *
 * @return The init counter value.
 *
 * This function initializes Lib and increments a counter of the number
 * of calls to it. The new counter value is then returned.
 *
 * @see my_app_lib_shutdown().
 */
EAPI int
my_app_lib_init(void);

/**
 * Shutdown Lib
 *
 * @return The init counter value.
 *
 * This function finalizes Lib and decrments a counter of the number
 * of calls to my_app_lib_init(). The new counter value is then returned.
 *
 * @see my_app_lib_shutdown().
 */
EAPI int
my_app_lib_shutdown(void);

EAPI const char *
my_app_lib_hello(void);

#ifdef __cplusplus
}
#endif

#endif   /* _MY_APP_LIB_H */
