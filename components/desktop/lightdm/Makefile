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
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lightdm
COMPONENT_VERSION=	1.28.0
COMPONENT_SUMMARY=	Light display manager
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:f20f599d8d7cf90b77a2df33c6e9e615abc443123b1b228de1c20a636aecfa07
COMPONENT_ARCHIVE_URL= \
	https://github.com/CanonicalLtd/lightdm/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/LightDM/
COMPONENT_FMRI=		system/display-manager/lightdm
COMPONENT_CLASSIFICATION=       Desktop (GNOME)/Sessions
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING.GPL3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i)

CPPFLAGS+= $(CPP_XPG7MODE)

CONFIGURE_BINDIR.64 = $(CONFIGURE_BINDIR.32)
CONFIGURE_SBINDIR.64 = $(CONFIGURE_SBINDIR.32)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-tests
CONFIGURE_OPTIONS += --with-greeter-session=lightdm-gtk-greeter
CONFIGURE_OPTIONS += --with-user-session=mate

CONFIGURE_ENV += XGETTEXT=/usr/gnu/bin/xgettext

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build:		$(BUILD_64)

install:	$(INSTALL_64)

REQUIRED_PACKAGES += library/gnome/yelp-tools
REQUIRED_PACKAGES += library/gnome/yelp-xsl
# libxml2 is required for xmllint
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += text/itstool
# Required by include of sys/soundcard.h in 13-save-audio-settings.patch
REQUIRED_PACKAGES += system/header/header-audio
# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/libxklavier
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxdmcp
