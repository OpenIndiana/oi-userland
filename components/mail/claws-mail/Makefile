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
# Copyright (c) 2020 Michal Nowak
# Copyright 2021 Gary Mills
#

SINGLE_PYTHON_VERSION= yes
USE_PARALLEL_BUILD= Yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		claws-mail
COMPONENT_VERSION=	4.3.0
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	The user-friendly, lightweight, and fast email client
COMPONENT_PROJECT_URL=	https://www.claws-mail.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:24a4d024c36f98add0e0b935cfa03cc6df01bc1b3f479a7a9d6df57705b04b2f
COMPONENT_ARCHIVE_URL=	https://www.claws-mail.org/download.php?file=releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		mail/claws-mail
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=	GPL-3
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

LDFLAGS += -lsocket

# gcc 14 complains about incompatible pointer types
CFLAGS += -Wno-error=implicit-function-declaration

COMPONENT_PREP_ACTION += ( cd $(@D) && autoreconf -fi )

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CPPFLAGS += $(CPPFLAGS.$(BITS))

CONFIGURE_OPTIONS += --disable-dependency-tracking
CONFIGURE_OPTIONS += --disable-fancy-plugin
CONFIGURE_OPTIONS += --disable-ldap
CONFIGURE_OPTIONS += --disable-perl-plugin
CONFIGURE_OPTIONS += --disable-rssyl-plugin
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-jpilot
CONFIGURE_OPTIONS += --disable-valgrind

CONFIGURE_ENV += PATH=/usr/bin/$(MACH64):/usr/bin
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Manually added build dependencies
# gnu-coreutils is needed for gecho (which is needed for providing the -n option):
REQUIRED_PACKAGES += file/gnu-coreutils

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libetpan
REQUIRED_PACKAGES += library/libical
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
