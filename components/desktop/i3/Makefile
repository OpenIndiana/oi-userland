#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Rick V
#

BUILD_BITS=32
include ../../../make-rules/shared-macros.mk
BUILD_STYLE=meson

COMPILER=gcc
COMPONENT_NAME=i3
COMPONENT_VERSION=4.19
COMPONENT_SUMMARY=improved tiling wm
COMPONENT_PROJECT_URL=https://i3wm.org
COMPONENT_FMRI=desktop/window-manager/i3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_ARCHIVE_URL=https://i3wm.org/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=sha256:aca48b03c0c70607826a1a91333065ff44d61774c152ddc9210fbc1627355872
COMPONENT_LICENSE=BSD-3

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk
CPPFLAGS+= -D_XOPEN_SOURCE=700
CPPFLAGS+= -D__EXTENSIONS__
LDFLAGS+= -lsocket -lnsl
CONFIGURE_OPTIONS+= -Dmans=true

REQUIRED_PACKAGES += desktop/dmenu
REQUIRED_PACKAGES += text/asciidoc
REQUIRED_PACKAGES += text/xmlto
# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libev
REQUIRED_PACKAGES += library/libyajl2
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxkbcommon
REQUIRED_PACKAGES += x11/library/xcb-util
REQUIRED_PACKAGES += x11/library/xcb-util-cursor
REQUIRED_PACKAGES += x11/library/xcb-util-keysyms
REQUIRED_PACKAGES += x11/library/xcb-util-wm
REQUIRED_PACKAGES += x11/library/xcb-util-xrm
