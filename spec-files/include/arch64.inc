#
# 64-bit platform settings for Solaris packages
#
# Copyright 2007 Sun Microsystems, Inc.
#
# Solaris.inc must be included before this file

%ifarch amd64 sparcv9

%ifarch amd64
%define _arch64 amd64
%else
%define _arch64 sparcv9
%endif

%define opt_sse2 0
%define opt_arch64 1
%define can_isaexec 1
%define gtk_doc_option --disable-gtk-doc

%if %option_with_gnu_iconv
%define arch_ldadd -L%{_libdir} -R%{_libdir} -Wl,-zignore -R/usr/gnu/lib/%{_arch64} -lgnuintl -lgnuiconv
%else
%define arch_ldadd -L%{_libdir} -R%{_libdir}
%endif

%ifarch amd64
%define opt_amd64 1
%define bld_arch	"amd64"
%else
%define opt_sparcv9 1
%define bld_arch	"sparcv9"
%endif

%if %debug_build
%define pkgbuild_postprocess /bin/true
%define _cc64_opt_level      -g
%define _cxx64_opt_level     -g
%define _gcc64_opt_level      -g
%define _gxx64_opt_level     -g
%else
%define _gcc64_opt_level      -O3
%define _gxx64_opt_level     -O3
%define _cc64_opt_level      -xO4 -xspace
%define _cxx64_opt_level     -xO3 -xspace
%endif

%ifarch sparc
%define gcc_optflags64           %_gcc64_opt_level -mcpu=ultrasparc -m64 -Xlinker -i %gcc_picflags
%define gcc_cxx_optflags64       %gcc_optflags64
%endif

%ifarch i386
%define gcc_optflags64           %_gcc64_opt_level -march=opteron -m64 -Xlinker -i -fno-omit-frame-pointer %gcc_picflags
%define gcc_cxx_optflags64       %gcc_optflags64
%endif

%ifarch sparc
%define suncc_optflags64           -i %_cc64_opt_level -xstrconst -xarch=v9 -xcode=pic32 -mr
%define suncc_cxx_optflags64       -i %_cxx64_opt_level -xarch=v9 -xcode=pic32 -mr -norunpath
%endif

%ifarch i386
%define suncc_optflags64           -i %_cc64_opt_level -xstrconst -m64 -Kpic -xregs=no%%frameptr
%define suncc_cxx_optflags64       -i %_cxx64_opt_level -xarch=generic64 -Kpic -pentium -mr -norunpath -xregs=no%%frameptr
%endif

%if %cc_is_gcc

%define picflags %gcc_picflags
%define optflags64 %gcc_optflags64
%define cxx_optflags64 %gcc_cxx_optflags64

%else
# cc is not gcc

%define picflags %suncc_picflags
%define optflags64 %suncc_optflags64
%define cxx_optflags64 %suncc_cxx_optflags64

%endif

%define optflags %optflags64 ${EXTRA_CFLAGS}
%define gcc_optflags %gcc_optflags64 ${EXTRA_CFLAGS}
%define cxx_optflags %cxx_optflags64 ${EXTRA_CXXFLAGS}
%define gcc_cxx_optflags %gcc_cxx_optflags64 ${EXTRA_CXXFLAGS}

%define _bindir		 %{_prefix}/bin/%{bld_arch}
%define _libdir		 %{_prefix}/lib/%{bld_arch}
%define _libexecdir	 %{_prefix}/lib/%{bld_arch}
%define _pkg_config_path %{_libdir}/pkgconfig:%{_datadir}/pkgconfig
# obsolete, don't use:
%define _pkg_config_path64 %{_prefix}/lib/%{_arch64}/pkgconfig:%{_datadir}/pkgconfig

%endif

# ChangeLog:
# 2009-12-30  Halton Huo <halton.huo@sun.com>
# - Remove cc_is_ssxx macros since we use ss12 always
# 2008-06-20  Laszlo (Laca) Peter  <laca@sun.com>
# - always define gcc_* macros, not only when cc_is_gcc, useful in spec
#   files that force using gcc
# 2008-03-30  Laszlo (Laca) Peter  <laca@sun.com>
# - use -m64 with ss12
# 2007-09-28  Laszlo (Laca) Peter  <laca@sun.com>
# - add /usr/gnu/lib/%{_arch64} to RPATH and link with GNU libintl and libiconv
#   when building with the --with-gnu-iconv option
# 2007-03-20  Doug Scott <dougs@truemail.co.th>
# - Added %_cc64_opt_level to suncc_optflags64 for i386
# 2007-03-19  Doug Scott <dougs@truemail.co.th>
# - Fixed -fno-omit-frame-pointer flag
# 2007-03-15  Laszlo (Laca) Peter  <laca@sun.com>
# - renamed from amd64.inc
# - updated to work for either amd64 or sparcv9
# 2007-03-12  Doug Scott  <dougs@truemail.co.th>
