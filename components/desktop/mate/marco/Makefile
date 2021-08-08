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
# Copyright 2020 Michal Nowak
#

MATE_CATEGORY=	APP
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		marco
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	0
COMPONENT_SUMMARY=	MATE Window Manager
COMPONENT_ARCHIVE_HASH=	sha256:f63c08cd8b07450ab3e33a04605c4f9e69522358884273b3cbcf30275eee5b05
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = cd $(@D)  && NOCONFIGURE=1 ./autogen.sh;\
	$(GSED) -i '/_XOPEN_SOURCE/d' $(@D)/src/tools/marco-mag.c; \
	$(GSED) -i '/_POSIX_C_SOURCE/d' $(@D)/src/core/util.c; \
	$(GSED) -i '/_XOPEN_SOURCE/d' $(@D)/src/ui/preview-widget.c

CFLAGS+=-D__EXTENSIONS__
CFLAGS+=-std=gnu99

CONFIGURE_OPTIONS+= --enable-maintainer-mode
CONFIGURE_OPTIONS+= --enable-compositor
CONFIGURE_OPTIONS+= --enable-xinerama

COMPONENT_BUILD_ENV += CPPFLAGS="$(CPPFLAGS)"

# Build dependencies
REQUIRED_PACKAGES += gnome/zenity
REQUIRED_PACKAGES += text/itstool

# Needed for autogen.sh
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
REQUIRED_PACKAGES += x11/library/libxpresent
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
