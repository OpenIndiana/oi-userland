dnl 
dnl
dnl

AC_ARG_WITH(sasldir, [  --with-sasldir=DIR    set the directory where
			  plugins will be installed, including $(MACH64),
  sasldir=$withval,
  sasldir=/usr/lib/sasl2)
AC_DEFINE_UNQUOTED(SASLDIR, "$sasldir", [Installtime plugin location])
AC_SUBST(sasldir)

