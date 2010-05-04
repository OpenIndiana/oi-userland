#
# Macro definitions for Solaris packages
#
# Copyright 2008 Sun Microsystems, Inc.
#

%include prod.inc
%include options.inc

SUNW_Pkg_AllZones:         false
SUNW_Pkg_Hollow:           false
SUNW_Pkg_ThisZone:         false

%define cc_is_gcc %(test "x`basename $CC`" = xgcc && echo 1 || echo 0)

%define is_nevada %(test `uname -r` = 5.11 && echo 1 || echo 0)
%define is_s10    %(test `uname -r` = 5.10 && echo 1 || echo 0)
%define _patch_options --fuzz=0 --unified

SUNW_Category:             %{default_category}
SUNW_HotLine:              Please contact your local service provider
SUNW_MaxInst:              1000
SUNW_Rev:		   110.0.4.%(date +%Y.%m.%d.%H.%M)
# no such file so this will break the build if the package
# does not specify a copyright file:
SUNW_Copyright:            error-no-copyright

%define _libexecdir        %{_prefix}/lib
%define _mandir		   %{_datadir}/man

# by default we don't build optimised versions
%define opt_sparcv9 0
%define opt_amd64   0
%define opt_sse2    0
# opt_arch64 means opt_sparcv9 or opt_amd64
%define opt_arch64  0
# can_isaexec gets redefined to 1 if multiple isas are built
%define can_isaexec 0
%ifarch sparc
%define base_isa sparcv7
%define base_arch sparc
%else
%define base_isa i86
%define base_arch i386
%endif

%if %option_with_gnu_iconv
%define arch_ldadd -Wl,-zignore -R/usr/gnu/lib -lgnuintl -lgnuiconv
%else
%define arch_ldadd
%endif
%define ldadd

%if %debug_build
%define _ldflags           %arch_ldadd %ldadd ${EXTRA_LDFLAGS}
%else
%define _ldflags           %arch_ldadd %ldadd -Wl,-zignore -Wl,-zcombreloc -Wl,-Bdirect ${EXTRA_LDFLAGS}
%endif

%define gcc_picflags -fPIC -DPIC
%define suncc_picflags -KPIC

# ifarch doesn't support checking for sse2
# this macros allows you to use %if %arch_sse2 instead
%define arch_sse2 %(isainfo -x | grep sse2 > /dev/null && echo 1 || echo 0)

# temporary, until all spec files are converted to the new multi-isa build
# technique
%ifarch amd64 sparcv9
%include arch64.inc
%endif

%include base.inc

%define _basedir           /usr
%define _subdir            
%define _prefix		   %{_basedir}
%define _sysconfdir	   /etc
%define _localstatedir	   /var
%define _localedir	   %{_datadir}/locale
%define _pkg_config_path   %{_libdir}/pkgconfig:%{_datadir}/pkgconfig

# ChangeLog:
# 2009-12-30  Halton Huo <halton.huo@sun.com>
# - Remove cc_is_ssxx macros since we use ss12 always
# 2008-10-29  Laszlo (Laca) Peter  <laca@sun.com>
# - respect $CC when checking compiler version
# 2008-04-18  Laszlo (Laca) Peter  <laca@sun.com>
# - set default copyright to "error-no-copyright" which is not the name
#   of a file, so it will break the build if a package has no copyright file
# 2008-03-30  Laszlo (Laca) Peter  <laca@sun.com>
# - define cc_is_ss11 and cc_is_ss12
# 2007-09-28  Laszlo (Laca) Peter  <laca@sun.com>
# - copy arch_ldadd definition from base.inc
# 2007-09-27  Laszlo (Laca) Peter  <laca@sun.com>
# - move configurable build options to options.inc and include
#   options.inc
# 2007-04-05  Laszlo (Laca) Peter  <laca@sun.com>
# - fix _ldflags so that it includes the architecture specific flags
# 2007-03-15  Laszlo (Laca) Peter  <laca@sun.com>
# - move product specific tags and macros to prod.inc
# - define can_isaexec, base_isa, base_arch
# - define arch_sse2
# - move 32-bit compiler flags to base.inc and include base.inc
# - move 64-bit compiler flags to arch64.inc and include it temporarily,
#   but it will not be needed once all spec files that build 64-bit are
#   rewritten to the new style
# 2007-01-28  Laszlo Peter  <laca@sun.com>
# - define %is_s10
# 2006-12-06  Damien Carbery  <damien.carbery@sun.com>
# - Bump SUNW_ProdVers and default_pkg_version to 2.17.3.
# 2006-11-23  Damien Carbery  <damien.carbery@sun.com>
# - Bump SUNW_ProdVers and default_pkg_version to 2.17.1.
# 2006-11-03  Laszlo Peter  <laca@sun.com>
# - define %gtk_doc_option, lets the user disable building gtk-docs
#   using --without-gtk-doc; also added comments about usage
# 2006-10-03  Laszlo Peter  <laca@sun.com>
# - define %_patch_options, this specifies extra options for gpatch when
#   using pkgbuild 1.1.1 or later
# 2006-10-03  Damien Carbery <damien.carbery@sun.com>
# - Bump SUNW_ProdVers and default_pkg_version to 2.16.1.
# 2006-09-18  Laszlo Peter  <laca@sun.com>
# - define cxx_optflags64
# 2006-08-23  Laszlo Peter  <laca@sun.com>
# - define _localstatedir
# 2006-06-02  Laszlo Peter  <laca@sun.com>
# - add the date string back into REV
# 2005-11-28  Laszlo Peter  <laca@sun.com>
# - add -z combreloc and -Bdirect to the LDFLAGS
# 2005-10-23  Laszlo Peter  <laca@sun.com>
# - define debug_build (if --with-debug is used) and build_l10n
#   (when --with-l10n is used)  build_l10n will disable building
#   the l10n packages but needs changes in the spec files to work;
#   debug_build is already functional: replaces the optimisation flags
#   with -g and disables stripping the binaries. (Yay!)
# 2005-10-14  Laszlo Peter  <laca@sun.com>
# - define _ldflags
# 2005-09-19  Laszlo Peter  <laca@sun.com>
# - add -xregs=no%frameptr (Sun CC) or -fomit-frame-pointers (gcc)
#   flags to enable dtrace get stack traces
# 2005-09-17  Laszlo Peter  <laca@sum.com>
# - define %picflags and add them to the gcc CFLAGS otherwise most things
#   seem to break
# 2005-09-16  Laszlo Peter  <laca@sun.com>
# - define cc_is_gcc and define gcc specific compiler flags
# 2005-09-15  Brian Cameron  <brian.cameron@sun.com>
# - Backout debug lines I accidently committed to this file.
# 2005-07-14  Laszlo Peter  <laca@sun.com>
# - update product version to 2.10
# 2004-11-01  Laszlo Peter  <laca@sun.com>
# - temporarily removed -O for amd64 to stop gtk-demo crashing
# 2004-10-13  Laszlo Peter  <laca@sun.com>
# - defined _pkg_config_path64
# 2004-10-02  Laszlo Peter  <laca@sun.com>
# - defined jds_version
# 2004-10-02  Joseph Townsend <jan@eng.sun.com>
# - Create 64bit libraries for Solaris
# 2004-08-12  Shirley Woo  <shirley.woo@sun.com>
# - Updated SUNW_Category for G2.6 packages to 2.6.0
# 2004-07-23  Laszlo Peter  <laca@sun.com>
# - Changed default copyright notice to default-copyright.txt
# - Prefixed REV with 9.7.2
# 2004-06-26  Shirley Woo  <shirley.woo@sun.com>
# - Changed install location to /usr/...
# 2004-06-21  Laszlo Peter  <laca@sun.com>
# - descrease C++ optimisation level to xO3
# - define _pkg_config_path
# 2004-05-03  Laszlo Peter  <laca@sun.com>
# - define _basedir
# 2004-04-14  Laszlo Peter  <laca@sun.com>
# - change CATEGORY to GNOME2,application,JDS3
# 2004-02-28  Laszlo Peter  <laca@sun.com>
# - add -mr and -xtrconst options, -xpentium on intel.
# - define cxx_optflags for CC compilation
