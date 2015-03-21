AC_INIT(src/imf-selector)
AC_PROG_INTLTOOL([0.23])

AM_PATH_PYTHON

PACKAGE=imf-selector
VERSION=1.0
GETTEXT_PACKAGE=$PACKAGE
AC_SUBST(GETTEXT_PACKAGE)

AM_INIT_AUTOMAKE($PACKAGE, $VERSION, no-define)
AC_DEFINE(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE")

AC_PROG_INSTALL

ALL_LINGUAS="de es fr it ja ko pt_BR zh_CN zh_TW"
AM_GLIB_GNU_GETTEXT

AM_MAINTAINER_MODE

AC_OUTPUT([
Makefile
src/Makefile
src/icons/Makefile
data/Makefile
po/Makefile.in
help/Makefile
help/C/Makefile
])
