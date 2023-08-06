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

BUILD_BITS= 64
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gexiv2
COMPONENT_MJR_VERSION=	0.14
COMPONENT_VERSION= $(COMPONENT_MJR_VERSION).2
COMPONENT_SUMMARY= GObject wrapper around the Exiv2 photo metadata library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:2a0c9cf48fbe8b3435008866ffd40b8eddb0667d2212b42396fdf688e93ce0be
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/gexiv2/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/gexiv2
COMPONENT_FMRI= image/library/gexiv2
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += PYVER=$(PYTHON_VERSION)

CONFIGURE_OPTIONS    += -Dtests=true

# gobject-introspection requires this
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages; \
	$(MV) $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/site-packages/* $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/; \
	$(PYTHON) -m compileall $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages;

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/Ok:/p" ' \
	'-e "/Expected Fail:/p" ' \
	'-e "/^Fail:/p" ' \
	'-e "/Unexpected Pass:/p" ' \
	'-e "/Skip:/p" ' \
	'-e "/Timeout:/p" ' \

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/exiv2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
