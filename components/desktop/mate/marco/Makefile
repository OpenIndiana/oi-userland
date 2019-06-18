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

BUILD_BITS=		64

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		marco
COMPONENT_MJR_VERSION=	1.22
COMPONENT_MNR_VERSION=	3
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=	http://www.mate-desktop.org
COMPONENT_SUMMARY=	MATE Window Manager
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:0a3979f0ba9855a6dff5b889c619d07bcea52df29c354976f018d71093c45139
COMPONENT_ARCHIVE_URL=	http://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2, LGPLv2, FDLv1.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_FMRI=		desktop/mate/$(COMPONENT_NAME)

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = cd $(@D)  && NOCONFIGURE=1 ./autogen.sh;\
	$(GSED) -i '/_POSIX_C_SOURCE/d' $(@D)/src/core/util.c; \
	$(GSED) -i '/_XOPEN_SOURCE/d' $(@D)/src/compositor/compositor-xrender.c; \
	$(GSED) -i '/_XOPEN_SOURCE/d' $(@D)/src/core/delete.c; \
	$(GSED) -i '/_XOPEN_SOURCE/d' $(@D)/src/core/keybindings.c; \
	$(GSED) -i '/_XOPEN_SOURCE/d' $(@D)/src/core/main.c; \
	$(GSED) -i '/_XOPEN_SOURCE/d' $(@D)/src/core/window-props.c; \
	$(GSED) -i '/_XOPEN_SOURCE/d' $(@D)/src/ui/preview-widget.c

CFLAGS+=-D__EXTENSIONS__
CFLAGS+=-std=gnu99

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --localstatedir=/var/lib
CONFIGURE_OPTIONS+= --enable-maintainer-mode
CONFIGURE_OPTIONS+= --enable-xinerama

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CPPFLAGS="$(CPPFLAGS)"

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
