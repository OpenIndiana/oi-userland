#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS=		64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
# Also, for now, all things built for C++11 require gcc.
COMPILER=gcc
include ../../../make-rules/shared-macros.mk

# Despite its name, evolution-data-server is no longer just a backend for the
# Evolution Mail Client; it is also a backend for various bits of data that
# GNOME stores and various components now expect it to be present.

COMPONENT_NAME=		evolution-data-server
COMPONENT_VERSION=	3.18.2
COMPONENT_ARCHIVE_HASH= \
	sha256:5942fc1cf395acdc15425939d83824d861d01c57225ee3fc8c1d77009468ce9b
COMPONENT_BUGDB=        gnome/libraries

TPNO=			25795

# Needs gobject-introspection, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# __EXTENSIONS__ required for timezone, altzone variables.
CFLAGS += -D__EXTENSIONS__ -DHAVE_SUN_KRB5
CXXFLAGS += -std=c++11 -D__EXTENSIONS__ -DHAVE_SUN_KRB5
CPPFLAGS += -I/usr/include/kerberosv5/
CFLAGS += $(XPG6MODE)

# Our NSS/NSPR libraries have their own private copy of sqlite3 which is
# different than the system-wide one; to avoid the private copy, we explicitly
# set the sqlite3 library location.
CONFIGURE_ENV += SQLITE3_LIBS="-L$(USRLIB) -lsqlite3"
CONFIGURE_ENV += SYSTEM_MAIL_DIR="$(VARDIR)/mail"
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

CONFIGURE_OPTIONS += --disable-dot-locking
# Documentation target is busted.
CONFIGURE_OPTIONS += --disable-gtk-doc
CONFIGURE_OPTIONS += --disable-schemas-compile
CONFIGURE_OPTIONS += --disable-static
# Ubuntu-specific functionality.
CONFIGURE_OPTIONS += --disable-uoa
CONFIGURE_OPTIONS += --enable-file-locking=fcntl
CONFIGURE_OPTIONS += --enable-goa
CONFIGURE_OPTIONS += --enable-gtk
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --enable-largefile
CONFIGURE_OPTIONS += --enable-smime
CONFIGURE_OPTIONS += --enable-shared
# Required for other components.
CONFIGURE_OPTIONS += --enable-vala-bindings
CONFIGURE_OPTIONS += --enable-weather
CONFIGURE_OPTIONS += --with-krb5
CONFIGURE_OPTIONS += --with-pic
# Apparently, Solaris mail spool format is "broken".
CONFIGURE_OPTIONS += --with-broken-spool=yes
# XXX Neither ldap target builds on Solaris.
CONFIGURE_OPTIONS += --without-openldap
CONFIGURE_OPTIONS += --without-sunldap

# A pkg-config file isn't shipped in Solaris for nss/nspr 64-bit, so configure
# will fail to find it; we workaround this by providing a one-off copy of the
# related pkg-config files and telling pkg-config to search our directory for
# them first.
CONFIGURE_ENV.64 += PKG_CONFIG_PATH="$(COMPONENT_DIR):$(PKG_CONFIG_PATH)"

# Required due to patches.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

# Delete once builds servers have libgweather installed
WEATHER_BASE = $(WS_COMPONENTS)/gnome/libgweather/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(WEATHER_BASE)$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS += -L $(WEATHER_BASE)$(USRLIB.$(BITS))

CONFIGURE_ENV+= LIBGWEATHER_CFLAGS="-DMESA_EGL_NO_X11_HEADERS -D_REENTRANT -D_POSIX_PTHREAD_SEMANTICS -D_REENTRANT -I$(WEATHER_BASE)/usr/include/libgweather-3.0 -I/usr/include/libsoup-2.4 -I/usr/include/libxml2 -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/$(MACH64)/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libdrm -I/usr/include/libpng14 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng14 -I/usr/include/glib-2.0 -I/usr/lib/$(MACH64)/glib-2.0/include"

# Delete this when build servers are installed with libical
ICAL_BASE = $(WS_COMPONENTS)/desktop/libical/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(ICAL_BASE)$(PKG_CONFIG_PATH.$(BITS))
LD_OPTIONS += -L $(ICAL_BASE)$(USRLIB)
CPPFLAGS += -I$(ICAL_BASE)$(USRINCDIR)/libical

# The dependency isn't installed, so add it manually since pkgdepend
# can't resolve them yet: 15708323
DEPENDED += $(WS_TOP)/components/gnome/libgweather/build/manifest-$(MACH)-libgweather.depend
DEPENDED += $(WS_TOP)/components/desktop/libical/build/manifest-$(MACH)-libical.depend

# Temporary until dependencies are all on build machines
REQUIRED_PACKAGES += $(shell $(GSED) -n -e '/GSED/d' -e 's/REQUIRED_PACKAGES +=//p' ../libgweather/Makefile)
REQUIRED_PACKAGES += $(shell $(GSED) -n -e '/GSED/d' -e 's/REQUIRED_PACKAGES +=//p' ../../desktop/libical/Makefile)
#end Delete

# for the tests
unexport SHELLOPTS
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/libgdata
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/gnome/gnome-online-accounts
REQUIRED_PACKAGES += library/gnome/libsecret
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libical
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/security/nss
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += security/kerberos-5/kdc
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/security/gss
