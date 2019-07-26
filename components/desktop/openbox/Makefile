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
# Copyright (c) 2017 Dariusz Sendkowski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openbox
COMPONENT_VERSION=	3.6.1
COMPONENT_REVISION=     2
COMPONENT_PROJECT_URL=	http://openbox.org
COMPONENT_SUMMARY=	A minimalistic,highly configurable, next generation window manager with extensive standards support.
COMPONENT_FMRI=         desktop/window-manager/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:abe75855cc5616554ffd47134ad15291fe37ebbebf1a80b69cbde9d670f0e26d
COMPONENT_ARCHIVE_URL=	http://openbox.org/dist/openbox/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPL	
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV=	DEST_DIR=$(PROTO_DIR)
COMPONENT_INSTALL_ENV=	DEST_DIR=$(PROTO_DIR)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --libexecdir=$(USRBINDIR)

CONFIGURE_BINDIR.64=	$(CONFIGURE_BINDIR.32)

COMPONENT_PRE_BUILD_ACTION = \
	/usr/bin/find $(SOURCE_DIR) -name openbox-xdg-autostart \
		-exec $(GSED) -i -e 's/env python/python$(PYTHON_VERSION)/' "{}" \; ;

CONFIGURE_ENV+= PYTHON=$(PYTHON)

LDFLAGS += -lsocket

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/python/python-xdg-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
