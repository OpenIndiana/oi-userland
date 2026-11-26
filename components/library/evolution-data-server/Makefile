#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2026 isoriano1968
#

# evolution-data-server 3.50.3 as in Solaris 11.4 (solaris-userland
# components/gnome/evolution-data-server @9d7a655); gnome-shell's calendar
# server needs libecal.  No GNOME Online Accounts, OAuth2/WebKit, LDAP or
# vala bindings, no Kerberos.  Solaris' 01-cmake (hard-coded /usr/lib/mps NSS paths) is
# not needed: OI has nss.pc and nspr.pc.  Solaris' icu patch is
# replaced by LDFLAGS += -licuuc (it only applied on top of 01-cmake).

BUILD_BITS=		64
BUILD_STYLE=		cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		evolution-data-server
HUMAN_VERSION=		3.50.3
COMPONENT_PROJECT_URL=	https://gitlab.gnome.org/GNOME/evolution-data-server
COMPONENT_SUMMARY=	Evolution Data Server - address book and calendar backends
COMPONENT_ARCHIVE_HASH=	\
	sha256:225d70b6a40268f225c2ac428ee5eb52d5a6fda2602955d50a24970526fe2452
COMPONENT_FMRI=		library/desktop/evolution-data-server
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.0-only
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

CFLAGS +=		-D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS
# POSIX iconv() prototype (char **), as Solaris: illumos gives it with _XPG6.
CFLAGS +=		$(XPG6MODE)
# per-thread errno on illumos (GLib programs are threaded)
CFLAGS +=		-D_REENTRANT
# getaddrinfo() & co. are in libsocket/libnsl on illumos (in libc on Solaris 11.4)
LDFLAGS +=		-lsocket -lnsl
# camel needs libicuuc too (its CMake links only ICU_LDFLAGS for icu-i18n);
# this is what Solaris' icu.patch did.
LDFLAGS +=		-licuuc
CXXFLAGS +=		-std=c++17 -D__EXTENSIONS__

CMAKE_OPTIONS +=	-DSYSCONF_INSTALL_DIR=$(ETCDIR)
CMAKE_OPTIONS +=	-DLIBEXEC_INSTALL_DIR=$(USRLIBEXECDIR)
CMAKE_OPTIONS +=	-DGETTEXT_XGETTEXT_EXECUTABLE=/usr/gnu/bin/xgettext
CMAKE_OPTIONS +=	-DENABLE_GOA=OFF
CMAKE_OPTIONS +=	-DENABLE_GOOGLE=OFF
CMAKE_OPTIONS +=	-DENABLE_OAUTH2_WEBKITGTK=OFF
CMAKE_OPTIONS +=	-DENABLE_OAUTH2_WEBKITGTK4=OFF
CMAKE_OPTIONS +=	-DENABLE_EXAMPLES=OFF
CMAKE_OPTIONS +=	-DENABLE_INTROSPECTION=ON
CMAKE_OPTIONS +=	-DENABLE_VALA_BINDINGS=OFF
CMAKE_OPTIONS +=	-DENABLE_GTK_DOC=OFF
CMAKE_OPTIONS +=	-DENABLE_INSTALLED_TESTS=OFF
CMAKE_OPTIONS +=	-DENABLE_TESTS=OFF
CMAKE_OPTIONS +=	-DWITH_OPENLDAP=OFF
# illumos has no public libkrb5 (Solaris does); Kerberos is only for
# GSSAPI mail logins in camel, which the GNOME Shell calendar does not use.
CMAKE_OPTIONS +=	-DWITH_KRB5=OFF
CMAKE_OPTIONS +=	-DWITH_LIBDB=OFF
CMAKE_OPTIONS +=	-DWITH_SYSTEMDUSERUNITDIR=OFF
CMAKE_OPTIONS +=	-DCMAKE_POLICY_VERSION_MINIMUM=3.5

CONFIGURE_ENV +=	PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV +=	PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += developer/build/cmake
REQUIRED_PACKAGES += developer/gperf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += gnome/config/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu-79
REQUIRED_PACKAGES += library/libical
# iconv-detect needs ISO-2022-JP <-> UTF-8 (also used at run time by camel)
REQUIRED_PACKAGES += system/library/iconv/extra
REQUIRED_PACKAGES += system/library/iconv/unicode
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libsoup3
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
