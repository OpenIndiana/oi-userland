#
# Base (32-bit) platform settings for Solaris packages
#
# Copyright 2007 Sun Microsystems, Inc.
#
# Solaris.inc must be included before this file

%ifarch sparc
%define bld_arch        "sparc"
%else
%define bld_arch	"i386"
%endif

%define opt_arch64 0
%define opt_sparcv9 0
%define opt_amd64 0
%define opt_sse2 0

# use --without-gtk-doc to disable building gtk-docs (it takes quite
# a while to build them)
# default: build gtk-doc API docs
%define gtk_doc_option %{?!_without_gtk_doc:--enable-gtk-doc}%{?_without_gtk_doc:--disable-gtk-doc}

%if %option_with_gnu_iconv
%define arch_ldadd -Wl,-zignore -R/usr/gnu/lib -lgnuintl -lgnuiconv
%else
%define arch_ldadd
%endif

%if %debug_build
%define pkgbuild_postprocess /bin/true
%define _cc_opt_level      -g
%define _cxx_opt_level     -g
%define _gcc_opt_level     -g
%define _gxx_opt_level     -g
%else
%define _gcc_opt_level     -O3
%define _gxx_opt_level     -O3
%define _cc_opt_level      -xO4 -xspace
%define _cxx_opt_level     -xO3 -xspace
%endif

%ifarch sparc
%define gcc_optflags           %_gcc_opt_level -mv8plus -Xlinker -i %gcc_picflags
%define gcc_cxx_optflags       %_gxx_opt_level -mv8plus -Xlinker -i %gcc_picflags
%endif

%ifarch i386
%define gcc_optflags           %_gcc_opt_level -march=i586 -Xlinker -i -fno-omit-frame-pointer %gcc_picflags
%define gcc_cxx_optflags       %_gxx_opt_level -march=i586 -Xlinker -i -fno-omit-frame-pointer %gcc_picflags
%endif

%ifarch sparc
%define suncc_optflags           -i %_cc_opt_level -xstrconst -xarch=v8a -mr -xmemalign=4i
%define suncc_cxx_optflags       -i %_cxx_opt_level -xarch=v8a -mr -norunpath -compat=5
%endif

%ifarch i386
%define suncc_optflags           -i %_cc_opt_level -xstrconst -xpentium -mr -xregs=no%%frameptr
%define suncc_cxx_optflags       -i %_cxx_opt_level -pentium -mr -norunpath -xregs=no%%frameptr -compat=5
%endif

%if %cc_is_gcc

%define picflags %gcc_picflags
%define optflags %gcc_optflags
%define cxx_optflags %gcc_cxx_optflags

%else
# cc is not gcc

%define picflags %suncc_picflags
%define optflags %suncc_optflags ${EXTRA_CFLAGS}
%define cxx_optflags %suncc_cxx_optflags ${EXTRA_CXXFLAGS}

%endif

%define _bindir		 %{_prefix}/bin
%define _libdir		 %{_prefix}/lib
%define _libexecdir	 %{_prefix}/lib
%define _pkg_config_path %{_libdir}/pkgconfig:%{_datadir}/pkgconfig
%define _sysconfdir      /etc

# ChangeLog:
# 2008-09-13  Laszlo (Laca) Peter  <laca@sun.com>
# - add -compat=5 option to Sun Studio CXXFLAGS as required by PSARC/2002/348
# 2007-09-28  Laszlo (Laca) Peter  <laca@sun.com>
# - add /usr/gnu/lib to the RUNPATH and link with GNU libintl and libiconv
#   when building with the --with-gnu-iconv option
# 2007-08-09  Laszlo (Laca) Peter  <laca@sun.com>
# - delete cc_is_gcc conditional when setting _gcc_opt_level,
#   because we want this set anyway so it can be used in spec
#   files that force gcc
# 2007-05-17  Laszlo (Laca) Peter  <laca@sun.com>
# - add -xmemalign=4i for sparc builds for binary compatibility with
#   apps compiled with earlier versions of Sun Studio, fixes 6457446
# 2007-04-05  Laszlo (Laca) Peter  <laca@sun.com>
# - fix cxx_optflags: use EXTRA_CXXFLAGS and not EXTRA_LDFLAGS
# 2007-03-19  Doug Scott <dougs@truemail.co.th>
# - Fixed -fno-omit-frame-pointer flag
# 2007-03-15  Laszlo (Laca) Peter  <laca@sun.com>
# - copied from x86_sse2.inc
# - new include file that resets macros to their default (32-bit build)
#   values
# 2007-03-12  Doug Scott  <dougs@truemail.co.th>
