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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pidgin
COMPONENT_VERSION=	2.10.11
COMPONENT_PROJECT_URL=	http://www.pidgin.im
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:f2ae211341fc77efb9945d40e9932aa535cdf3a6c8993fe7919fca8cc1c04007
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/pidgin

TPNO=			21690

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk

# Cyrus SASL is S12-only (at least for evaluation builds).
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32=
INSTALL_32=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/ips.mk

# Need to pick up the Studio compiler as some Makefiles just use "cc".
# Need to pick up the GNU version of xgettext.
PATH=$(dir $(CC)):$(SPRO_VROOT)/bin:/usr/gnu/bin:/usr/bin

CFLAGS +=		-DG_IMPLEMENT_INLINES -DG_HAVE_ISO_VARARGS

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; \
	glib-gettextize -f ; \
	libtoolize --force ; \
	intltoolize --force --copy --automake ; \
	aclocal -I . ; \
	autoheader ; \
	automake -a -c -f ; \
	autoconf )

# Needed to get libpurple to link properly.
LIBS += -lresolv
CONFIGURE_ENV +=	LIBS="$(LIBS)"
CONFIGURE_ENV +=	PKG_CONFIG_PATH=/usr/lib/64/pkgconfig/gnutls-3

# Version of Perl to use.
PERL_VERSION =  5.20

CONFIGURE_ENV += "ac_cv_path_perlpath=/usr/perl5/$(PERL_VERSION)/bin/perl"

CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	--enable-cyrus-sasl
CONFIGURE_OPTIONS +=	--disable-nss
CONFIGURE_OPTIONS +=	--enable-gnutls
CONFIGURE_OPTIONS +=	--with-gnutls-includes=/usr/include/gnutls-3
CONFIGURE_OPTIONS +=	--with-gnutls-libs=/usr/lib/64/gnutls-3
CONFIGURE_OPTIONS +=	--enable-gnome-keyring
CONFIGURE_OPTIONS +=	--disable-gevolution
CONFIGURE_OPTIONS +=	--enable-cap
CONFIGURE_OPTIONS +=	--disable-meanwhile
CONFIGURE_OPTIONS +=	--disable-nm
CONFIGURE_OPTIONS +=	--disable-consoleui
CONFIGURE_OPTIONS +=	--disable-vv

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS +=	V=1

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_64)

build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(NO_TESTS)

system-test:	$(NO_TESTS)

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtkspell
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-keyring
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/python/python-dbus-27
REQUIRED_PACKAGES += runtime/perl-520
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libsasl2
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxscrnsaver
