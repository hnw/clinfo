#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE(foreign)

AC_CONFIG_SRCDIR([clinfo.c])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Enable support for OpenCL
AX_OPENCL([C])
CFLAGS="$CL_CFLAGS $CFLAGS"
CPPFLAGS="$CL_CFLAGS $CPPFLAGS"
LIBS="$CL_LIBS $LIBS"
AC_SUBST(CL_CFLAGS)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
