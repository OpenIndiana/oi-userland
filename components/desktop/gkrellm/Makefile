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
# Copyright (c) 2015 Alexander Pyhalov
#

BUILD_BITS=			64
BUILD_STYLE=		justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gkrellm
COMPONENT_VERSION=	2.3.11
COMPONENT_PROJECT_URL=	http://gkrellm.srcbox.net/
COMPONENT_SUMMARY=	Popular (ubiquitous) Gtk-based system monitor
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:1ee0643ed9ed99f88c1504c89d9ccb20780cf29319c904b68e80a8e7c8678c06
COMPONENT_ARCHIVE_URL=	http://gkrellm.srcbox.net/releases/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE= GPLv3
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI= desktop/system-monitor/gkrellm

TEST_TARGET:		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=/usr/bin/$(MACH64):$(PATH.gnu)

COMPONENT_BUILD_ENV += enable_nls=1
COMPONENT_BUILD_ENV += LOCALEDIR=/usr/share/locale
COMPONENT_BUILD_ENV += LINK_FLAGS="-lsocket -lnsl -lkstat -lkvm -ldevinfo"
COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV += PATH=$(PATH)

COMPONENT_INSTALL_ENV += PREFIX=/usr

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
