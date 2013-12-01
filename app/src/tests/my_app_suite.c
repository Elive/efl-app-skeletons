#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */

#include <check.h>
#include "Lib.h"

START_TEST (test_my_app_lib)
{
   ck_assert(my_app_lib_init() == 1);
   ck_assert(my_app_lib_init() == 2);

   ck_assert(strcmp(my_app_lib_hello(), "Hello from the EFL world") == 0);

   ck_assert(my_app_lib_shutdown() == 1);
   ck_assert(my_app_lib_shutdown() == 0);
   ck_assert(my_app_lib_shutdown() == 0);
}
END_TEST

Suite *
my_app_suite (void)
{
   Suite *s = suite_create ("Elm_Skel");

   TCase *tc_core = tcase_create ("Core");
   tcase_add_test (tc_core, test_my_app_lib);
   suite_add_tcase (s, tc_core);

   return s;
}

int
main(int argc EINA_UNUSED, char *argv[] EINA_UNUSED)
{
   int number_failed;
   Suite *s = my_app_suite();
   SRunner *sr = srunner_create(s);
   srunner_run_all(sr, CK_ENV);
   number_failed = srunner_ntests_failed(sr);
   srunner_free(sr);
   return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
