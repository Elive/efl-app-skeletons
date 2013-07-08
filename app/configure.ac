dnl Process this file with autoconf to produce a configure script.

# get rid of that stupid cache mechanism
rm -f config.cache

AC_INIT([elm_skel], [0.0.1], [jeremy@asynk.ch])
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

### Default options with respect to host

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

EFL_CHECK_COMPILER_FLAGS([ELM_SKEL], [-Wall -Wunused -Wextra -Wpointer-arith -Wno-missing-field-initializers -fvisibility=hidden -fdata-sections -ffunction-sections])
EFL_CHECK_LINKER_FLAGS([ELM_SKEL], [-fvisibility=hidden -fdata-sections -ffunction-sections -Wl,--gc-sections -fno-strict-aliasing -Wl,--as-needed -Wl,--no-copy-dt-needed-entries])

### Checks for programs

AC_PROG_CC

# pkg-config

PKG_PROG_PKG_CONFIG

# Check whether pkg-config supports Requires.private

if $PKG_CONFIG --atleast-pkgconfig-version 0.22; then
   pkgconfig_requires_private="Requires.private"
else
   pkgconfig_requires_private="Requires"
fi
AC_SUBST(pkgconfig_requires_private)

### Checks for libraries

# Evil library for compilation on Windows

ELM_SKEL_BUILD=""
case "$host_os" in
   mingw*)
      PKG_CHECK_MODULES([EVIL], [evil >= 1.0.0])
      AC_DEFINE([HAVE_EVIL], [1], [Set to 1 if Evil library is installed])
      requirement_elm_skel="evil ${requirement_elm_skel}"
      ELM_SKEL_BUILD="-DELM_SKEL_BUILD"
      ;;
esac
AC_SUBST(ELM_SKEL_BUILD)

# Dependencies for the library

requirement_elm_skel="elementary >= 1.7.0 evas >= 1.7.0 ecore-file >= 1.7.0 ecore >= 1.7.0 eet >= 1.7.0 eina >= 1.7.0 ${requirement_elm_skel}"
PKG_CHECK_MODULES([ELEMENTARY], [ $requirement_elm_skel ])

AC_SUBST(requirement_elm_skel)

# Checks for library functions.

AM_GNU_GETTEXT_VERSION([0.18])

### Checks for header files

EFL_CHECK_PATH_MAX

### Checks for compiler characteristics

AM_PROG_CC_C_O
AC_C_CONST
AC_PROG_CC_STDC
AC_HEADER_STDC

EFL_ATTRIBUTE_VECTOR

case "$host_os" in
   mingw32ce*)
      ELM_SKEL_CFLAGS="${ELM_SKEL_CFLAGS} -D_WIN32_WCE=0x0420"
      ;;
esac

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
   Makefile
   src/Makefile
   src/bin/Makefile
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
echo
