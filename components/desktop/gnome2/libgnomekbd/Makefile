#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
#

include ../../../../make-rules/shared-macros.mk

BUILD_STYLE=configure
COMPONENT_NAME= libgnomekbd

COMPONENT_VERSION= 2.91.92
COMPONENT_REVISION= 0
COMPONENT_SUMMARY= GNOME kbd library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:3c50c54ee3a74a1d7a17517d4d3e72237fe272770f05879d6053b4e8bc6fc8d8
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(basename $(COMPONENT_VERSION))/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/gnome/libgnomekbd
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING.LIB

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS+= -Wno-error=incompatible-pointer-types
CFLAGS+= -Wno-error=implicit-function-declaration

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libxklavier
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
