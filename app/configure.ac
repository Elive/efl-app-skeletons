dnl Process this file with autoconf to produce a configure script.

# get rid of that stupid cache mechanism
rm -f config.cache

PROJECT_VERSION([0], [0], [1], [dev])
AC_INIT([my_app], [v_ver], [jeremy@asynk.ch])
AC_PREREQ([2.65])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_HEADERS([config.h])
AH_TOP([
#ifndef __CONFIG_H__
#define __CONFIG_H__
])
AH_BOTTOM([
#endif /* __CONFIG_H__ */
])

AM_INIT_AUTOMAKE([1.10 dist-bzip2])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# this will speed up libtool checks
LT_PREREQ([2.2])
LT_INIT([win32-dll])
PROJECT_INIT

### Default options with respect to host

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

### Additional options to configure

# Build profile

AC_ARG_WITH([profile],
   [AC_HELP_STRING([--with-profile=PROFILE],
                   [use the predefined build profile, one of: dev, debug and release.
                    @<:@default=dev@:>@])],
   [build_profile=${withval}],
   [build_profile=def_build_profile])

case "${build_profile}" in
   dev|debug|release)
     ;;
   *)
     AC_MSG_ERROR([Unknown build profile --with-profile=${build_profile}])
     ;;
esac

# Tests

AC_ARG_WITH([tests],
   [AC_HELP_STRING([--with-tests=none|regular|coverage],
                   [choose testing method: regular, coverage or none.
                    @<:@default=none@:>@])],
   [build_tests=${withval}],
   [build_tests=auto])

want_coverage="no"
want_tests="no"
case "${build_tests}" in
   auto)
     if test "${build_profile}" = "dev"; then
        want_tests="yes"
     fi
     ;;
   regular)
     want_tests="yes"
     ;;
   coverage)
     want_tests="yes"
     want_coverage="yes"
     ;;
   none)
     ;;
   *)
     AC_MSG_ERROR([Unknown build tests option: --with-tests=${build_tests}])
     ;;
esac

### Checks for programs

AC_PROG_CC

# Check edje_cc
EFL_WITH_BIN([edje], [edje-cc], [edje_cc])
if test "x${edje_cc}" = "x" ; then
   AC_MSG_ERROR([Unable to find edje_cc binary.])
fi

# pkg-config

PKG_PROG_PKG_CONFIG

# Check whether pkg-config supports Requires.private

if $PKG_CONFIG --atleast-pkgconfig-version 0.22; then
   pkgconfig_requires_private="Requires.private"
else
   pkgconfig_requires_private="Requires"
fi
AC_SUBST(pkgconfig_requires_private)

# lcov

if test "${want_coverage}" = "yes" ; then
   AC_CHECK_PROG([have_lcov], [lcov], [yes], [no])
   if test "x${have_lcov}" = "xyes" ; then
      MY_APP_COV_CFLAGS="${MY_APP_COV_CFLAGS} -fprofile-arcs -ftest-coverage"
      MY_APP_COV_LIBS="${MY_APP_COV_LIBS} -lgcov"
      if test "x${prefer_assert}" = "xno"; then
         MY_APP_COV_CFLAGS="${MY_APP_COV_CFLAGS} -DNDEBUG"
      else
         MY_APP_COV_CFLAGS="${MY_APP_COV_CFLAGS} -g -O0 -DDEBUG"
      fi
   else
      AC_MSG_ERROR([lcov is not found])
   fi
fi

AC_SUBST(MY_APP_COV_LIBS)
AC_SUBST(MY_APP_COV_CFLAGS)
AM_CONDITIONAL([MY_APP_ENABLE_COVERAGE], [test "${want_coverage}" = "yes"])

# lout

AC_CHECK_PROG([have_lout], [lout], [yes], [no])
AM_CONDITIONAL(MY_APP_HAVE_DOC, test "x${have_lout}" = "xyes")

### Checks for libraries

# check unit testing library

if test "${want_tests}" = "yes"; then
   PKG_CHECK_MODULES([CHECK], [check >= 0.9.5])
fi
AM_CONDITIONAL([MY_APP_ENABLE_TESTS], [test "${want_tests}" = "yes"])

# Checks for library functions.

# Evil library for compilation on Windows

MY_APP_BUILD=""
case "$host_os" in
   mingw*)
      PKG_CHECK_MODULES([EVIL], [evil >= 1.0.0])
      AC_DEFINE([HAVE_EVIL], [1], [Set to 1 if Evil library is installed])
      requirement_my_app="evil ${requirement_my_app}"
      MY_APP_BUILD="-DMY_APP_BUILD"
      ;;
esac
AC_SUBST(MY_APP_BUILD)

# Dependencies for the library

requirement_my_app="elementary >= 1.7.0 evas >= 1.7.0 ecore-file >= 1.7.0 ecore >= 1.7.0 eet >= 1.7.0 eina >= 1.7.0 ${requirement_my_app}"
PKG_CHECK_MODULES([EFL], [ $requirement_my_app ])

AC_SUBST(requirement_my_app)

# Checks for library functions.

AM_GNU_GETTEXT_VERSION([0.18])

### Checks for header files

EFL_CHECK_PATH_MAX

### Checks for types

### Checks for structures

### Checks for compiler characteristics

AM_PROG_CC_C_O
AC_C_CONST
AC_PROG_CC_STDC
AC_HEADER_STDC

ELM_QUICKLAUNCH
EFL_ATTRIBUTE_VECTOR

case "$host_os" in
   mingw32ce*)
      MY_APP_CFLAGS="${MY_APP_CFLAGS} -D_WIN32_WCE=0x0420"
      ;;
esac

EFL_CHECK_COMPILER_FLAGS([MY_APP], [-Wall -Wunused -Wextra -Wpointer-arith -Wno-missing-field-initializers -fvisibility=hidden -fdata-sections -ffunction-sections])
EFL_CHECK_LINKER_FLAGS([MY_APP], [-fvisibility=hidden -fdata-sections -ffunction-sections -Wl,--gc-sections -fno-strict-aliasing -Wl,--as-needed -Wl,--no-copy-dt-needed-entries])

case "${build_profile}" in
   dev)
     dnl Check if compiler has a dodgy -Wshadow that emits errors when shadowing a global
     AC_MSG_CHECKING([whether -Wshadow generates spurious warnings])
     CFLAGS_save="${CFLAGS}"
     CFLAGS="${CFLAGS} -Werror -Wshadow"
     AC_TRY_COMPILE([int x;], [int x = 0; (void)x;],
       [AC_MSG_RESULT([no])
        EFL_CHECK_COMPILER_FLAGS([EFL], [-Wshadow])],
       [AC_MSG_RESULT([yes])])
     CFLAGS="${CFLAGS_save}"
     ;;

   debug)
     ;;

   release)
     ;;
esac

# CPU architecture specific assembly

### Checks for linker characteristics

lt_enable_auto_import=""
case "$host_os" in
   mingw*)
      lt_enable_auto_import="-Wl,--enable-auto-import"
      ;;
esac
AC_SUBST(lt_enable_auto_import)

### Output

AC_OUTPUT([
   my_app.pc
   Makefile
   src/Makefile
   data/Makefile
   data/desktop/Makefile
   data/desktop/my_app.desktop
   data/themes/Makefile
   data/themes/default/Makefile
   doc/Makefile
])

AC_OUTPUT

#####################################################################
## Info

echo
echo
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE $VERSION"
echo "------------------------------------------------------------------------"
echo
echo "Compilation................: make (or gmake)"
echo "  CPPFLAGS.................: $CPPFLAGS"
echo "  CFLAGS...................: $CFLAGS"
echo "  LDFLAGS..................: $LDFLAGS"
echo
echo "Installation...............: make install (as root if needed, with 'su' or 'sudo')"
echo "  prefix...................: $prefix"
echo "  edje_cc..................: ${edje_cc}"
echo
echo "Configuration...: ${COLOR_OTHER}profile=${build_profile} os=${host_os}${COLOR_RESET}"
echo
if test "${want_coverage}" = "yes"; then
echo "Tests...........: make lcov-check"
else
if test "${want_tests}" = "yes"; then
echo "Tests...........: make check"
else
echo "Tests...........: no"
fi
fi
if test "x${have_lout}" = "xyes"; then
echo "Tests...........: make doc"
fi
echo
