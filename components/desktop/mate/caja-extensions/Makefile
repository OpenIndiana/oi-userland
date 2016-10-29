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

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		caja-extensions
COMPONENT_VERSION=	1.14.0
COMPONENT_PROJECT_URL=	http://www.mate-desktop.org
COMPONENT_SUMMARY=	Set of extensions for Caja, the MATE file manager
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8f3630eb5e393d357423f94a3a1f9a32bab7dc610d1aaa811019ec710a1fdf06
COMPONENT_ARCHIVE_URL=	http://pub.mate-desktop.org/releases/1.14/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/File Managers
COMPONENT_FMRI=	desktop/mate/caja/caja-extensions
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION=  cd $(@D)  && NOCONFIGURE=1 ./autogen.sh

CONFIGURE_LIBEXECDIR.32 =   $(USRLIBDIR)/mate
CONFIGURE_LIBEXECDIR.64 =   $(USRLIBDIR)/mate
### TODO: CONFIGURE_LIBEXECDIR.64 should be different? Original was:
###CONFIGURE_OPTIONS+=  --libexecdir=/usr/lib/mate

CONFIGURE_OPTIONS+=	--disable-static

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += desktop/mate/caja
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/mate/mate-desktop
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
