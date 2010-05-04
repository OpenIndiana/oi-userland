#
# Macro definitions for optional features
#

#
# Option: --with-l10n
#
# use --with-l10n to build the SUNWfoo-l10n packages
# default: no l10n packages
#
%define option_with_l10n %{?_with_l10n:1}%{?!_with_l10n:0}
%define option_without_l10n %{!?_with_l10n:1}%{?_with_l10n:0}

# obsolete:
%define build_l10n %option_with_l10n

#
# Option: --with-debug
#
# use --with-debug to build binaries with debug info (-g) and not to strip
# them.
# default: don't include debug info and strip the binaries (strip -x)
#
%define option_with_debug %{?_with_debug:1}%{?!_with_debug:0}
%define option_without_debug %{!?_with_debug:1}%{?_with_debug:0}

# obsolete:
%define debug_build %option_with_debug

#
# Option: --without-gtk-doc
#
# use --without-gtk-doc to disable building gtk-docs (it takes quite
# a while to build them)
# default: build gtk-doc API docs
#
%define option_with_gtk_doc %{?!_without_gtk_doc:1}%{?_without_gtk_doc:0}
%define option_without_gtk_doc %{?_without_gtk_doc:1}%{?!_without_gtk_doc:0}

# macro to use as a configure option:
%define gtk_doc_option %{?!_without_gtk_doc:--enable-gtk-doc}%{?_without_gtk_doc:--disable-gtk-doc}

#
# Option: --with-fox
#
# use --with-fox to build JDS with the FOX project's X packages
# instead of the nevada X packages
# default: nevada
#
%define option_with_fox %{?_with_fox:1}%{?!_with_fox:0}
%define option_without_fox %{!?_with_fox:1}%{?_with_fox:0}

#
# Option: --with-gnu-iconv
#
# use --with-gnu-iconv to build JDS with the GNU libiconv and
# libintl implementations instead of the nevada libc implementations
# default: libc
#
%define option_with_gnu_iconv %{?_with_gnu_iconv:1}%{?!_with_gnu_iconv:0}
%define option_without_gnu_iconv %{!?_with_gnu_iconv:1}%{?_with_gnu_iconv:0}

#
# Option: --without-java
#
# use --without-java exclude the Java bits from the build and packages
# default: build java
#
%define option_with_java %{?!_without_java:1}%{?_without_java:0}
%define option_without_java %{?_without_java:1}%{?!_without_java:0}

#
# Option: --without-dt
#
# use --without-dt to remove dependency on /usr/dt "stuff" like dtlogin
# default: depend on /usr/dt
#
%define option_with_dt %{?!_without_dt:1}%{?_without_dt:0}
%define option_without_dt %{?_without_dt:1}%{?!_without_dt:0}

#
# Option: --with-sun-branding
#
# use --with-sun-branding to build JDS with Sun Solaris branding
# default: no Sun branding
#
%define option_with_sun_branding %{?_with_sun_branding:1}%{?!_with_sun_branding:0}
%define option_without_sun_branding %{!?_with_sun_branding:1}%{?_with_sun_branding:0}

#
# Option: --with-indiana-branding
#
# use --with-indiana-branding to build JDS with Indiana Solaris branding
# default: no Indiana branding
#
%define option_with_indiana_branding %{?_with_indiana_branding:1}%{?!_with_indiana_branding:0}
%define option_without_indiana_branding %{!?_with_indiana_branding:1}%{?_with_indiana_branding:0}

%if %option_with_sun_branding
%if %option_with_indiana_branding
%error You cannot enable both Sun Solaris and Indiana branding
%endif
%endif

#
# Option: --without-blueprint
#
# use --without-blueprint if you do not with to include the blueprint theme
# default: include blueprint
#
%define option_with_blueprint %{?!_without_blueprint:1}%{?_without_blueprint:0}
%define option_without_blueprint %{?_without_blueprint:1}%{?!_without_blueprint:0}

#
# Option: --without-apoc-adapter
#
# use --with-apoc-adapter to enable apoc adapter for SUNWfirefox
# default: not build apoc adapter
%define option_with_apoc_adapter %{?_with_apoc_adapter:1}%{?!_with_apoc_adapter:0}
%define option_without_apoc_adapter %{!?_with_apoc_adapter:1}%{?_with_apoc_adapter:0}

#
# Option: --with-moz-nss-nspr
#
# use --with-moz-nss-nspr to deliver Mozilla bundled nss, nspr libs
# for SUNWfirefox
# default: without Mozilla bundled nss, nspr libs
%define option_without_moz_nss_nspr %{?!_with_moz_nss_nspr:1}%{?_with_moz_nss_nspr:0}

#
# Option: --without-lightning
#
# use --without-lightning to disable building lightning for SUNWthunderbird
# default: build lightning
%define option_with_lightning %{?!_without_lightning:1}%{?_without_lightning:0}

# ChangeLog:
# 2009-05-25  - ginn.chen@sun.com
# - add option --without-lightning
# 2009-05-21  - ginn.chen@sun.com
# - add option --without-apoc-adapter, --with-moz-nss-nspr
# 2009-03-23  - dave.lin@sun.com
# - remove option --with-ff3
# 2008-05-22  - dave.lin@sun.com
# - add option --with-ff3 
# 2007-09-27  Laszlo (Laca) Peter  <laca@sun.com>
# - create
