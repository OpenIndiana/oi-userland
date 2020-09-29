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
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		claws-mail
COMPONENT_VERSION=	3.17.7
COMPONENT_PROJECT_URL=	https://www.claws-mail.org
COMPONENT_FMRI=		mail/claws-mail
COMPONENT_SUMMARY=	The user-friendly, lightweight, and fast email client
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:60b94649bc30ae79e057054e44afbe5fe29de0e77614b81505cff2204c02ddc8
COMPONENT_ARCHIVE_URL=	https://www.claws-mail.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPL-3
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION= Applications/Internet

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += ( cd $(@D) && autoreconf -fi )

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CPPFLAGS += $(CPPFLAGS.$(BITS))

CONFIGURE_OPTIONS += --disable-fancy-plugin
CONFIGURE_OPTIONS += --disable-ldap
CONFIGURE_OPTIONS += --disable-perl-plugin
CONFIGURE_OPTIONS += --disable-rssyl-plugin
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_ENV += PATH=/usr/bin/$(MACH64):/usr/bin
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

REQUIRED_PACKAGES += library/python/pygobject
REQUIRED_PACKAGES += library/python/pygtk2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += runtime/python-27
# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libgdata
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libetpan
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
