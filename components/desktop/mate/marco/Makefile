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
# Copyright 2016 Ken Mays
# Copyright 2016 Till Wegmueller
# Copyright 2019 Michal Nowak
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		marco
COMPONENT_MJR_VERSION=	1.22
COMPONENT_MNR_VERSION=	1
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=	http://www.mate-desktop.org
COMPONENT_SUMMARY=	MATE Window Manager
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:4e20f5ea006142f3e5c8931e2b354e1838cb9291ba245825ea82fa6611def7c8
COMPONENT_ARCHIVE_URL=	http://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2, LGPLv2, FDLv1.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_FMRI=		desktop/mate/$(COMPONENT_NAME)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = cd $(@D)  && NOCONFIGURE=1 ./autogen.sh;\
	$(GSED) -i '/_XOPEN_SOURCE/d' $(@D)/src/tools/marco-mag.c; \
	$(GSED) -i '/_POSIX_C_SOURCE/d' $(@D)/src/core/util.c; \
	$(GSED) -i '/_XOPEN_SOURCE/d' $(@D)/src/ui/preview-widget.c

CFLAGS+=-D__EXTENSIONS__
CFLAGS+=-std=gnu99

CONFIGURE_BINDIR.64 = $(CONFIGURE_BINDIR.32)

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --localstatedir=/var/lib
CONFIGURE_OPTIONS+= --enable-maintainer-mode
CONFIGURE_OPTIONS+= --enable-xinerama

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CPPFLAGS="$(CPPFLAGS)"

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += gnome/zenity
REQUIRED_PACKAGES += text/itstool
# Needed for autogen.sh
REQUIRED_PACKAGES += library/desktop/mate/mate-common
REQUIRED_PACKAGES += library/gnome/yelp-tools

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libgtop
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
