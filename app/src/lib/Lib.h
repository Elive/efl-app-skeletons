#ifndef _ELM_SKEL_LIB_H
#define _ELM_SKEL_LIB_H

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
 * @see elm_skel_lib_shutdown().
 */
EAPI int
elm_skel_lib_init(void);

/**
 * Shutdown Lib
 *
 * @return The init counter value.
 *
 * This function finalizes Lib and decrments a counter of the number
 * of calls to elm_skel_lib_init(). The new counter value is then returned.
 *
 * @see elm_skel_lib_shutdown().
 */
EAPI int
elm_skel_lib_shutdown(void);

EAPI const char *
elm_skel_lib_hello(void);

#ifdef __cplusplus
}
#endif

#endif   /* _ELM_SKEL_LIB_H */
