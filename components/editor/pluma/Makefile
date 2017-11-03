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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pluma
COMPONENT_MJR_VERSION=	1.18
COMPONENT_MNR_VERSION=	2
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=	http://mate-desktop.org/
COMPONENT_SUMMARY=	MATE text editor
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ff0f29d4eaa946cbb2b26bbdc2b2d5a308b2d16ec99ea384bcb13f1f3d1a09fc
COMPONENT_ARCHIVE_URL=	http://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI=         editor/pluma

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

LDFLAGS += -lnsl -lsocket

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					autoreconf -f )


CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--disable-static

COMPONENT_BUILD_ENV+=	CC="$(CC)"
COMPONENT_BUILD_ENV+=	CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += data/iso-codes
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtksourceview3
REQUIRED_PACKAGES += library/desktop/libpeas
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
