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
# Copyright 2020 Alexander Pyhalov
# Copyright 2021 Andreas Wacknitz
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gexiv2
COMPONENT_MJR_VERSION=	0.14
COMPONENT_VERSION= $(COMPONENT_MJR_VERSION).3
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= GObject wrapper around the Exiv2 photo metadata library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:21e64d2c56e9b333d44fef3f2a4b25653d922c419acd972fa96fab695217e2c8
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/gexiv2/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/gexiv2
COMPONENT_FMRI= image/library/gexiv2
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += PYVER=$(PYTHON_VERSION)

CONFIGURE_OPTIONS += -Dtests=true

# gobject-introspection requires this
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages; \
	$(MV) $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/site-packages/* $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/; \
	$(PYTHON) -m compileall $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages;

# Manually added build dependencies
REQUIRED_PACKAGES += developer/vala

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/exiv2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
