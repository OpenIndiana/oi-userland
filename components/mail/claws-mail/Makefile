#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2016 Sergey Avseyev
# Copyright (c) 2018 Michal Nowak
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		claws-mail
COMPONENT_VERSION=	3.16.0
COMPONENT_PROJECT_URL=	http://www.claws-mail.org
COMPONENT_FMRI=		mail/claws-mail
COMPONENT_SUMMARY=	The user-friendly, lightweight, and fast email client
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c212133d3d962129d8c7995c1c7d973faef2a8914481c0c74578217bf4c897ab
COMPONENT_ARCHIVE_URL=	http://www.claws-mail.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPL-3
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION= Applications/Internet

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION += ( cd $(@D) && autoreconf -fi )

CPPFLAGS += -I/usr/include/gnutls-3
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig/gnutls-3
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS.32 += -L/usr/lib/gnutls-3 -R/usr/lib/gnutls-3
LD_OPTIONS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

CPPFLAGS.32 = -D_FILE_OFFSET_BITS=64
CPPFLAGS += $(CPPFLAGS.$(BITS))

CONFIGURE_BINDIR.64 = /usr/bin

CONFIGURE_OPTIONS += --disable-fancy-plugin
CONFIGURE_OPTIONS += --disable-ldap
CONFIGURE_OPTIONS += --disable-perl-plugin
CONFIGURE_OPTIONS += --disable-rssyl-plugin
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_ENV.64 += PATH=/usr/bin/$(MACH64):/usr/bin
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libetpan
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
