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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2018 Michal Nowak
#

BUILD_STYLE = meson
BUILD_BITS = 64_and_32
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gdk-pixbuf
HUMAN_VERSION=		2.42.12
COMPONENT_SUMMARY=	GdkPixbuf: Image loading library
COMPONENT_ARCHIVE_HASH=	sha256:b9505b3445b9a7e48ced34760c3bcb73e966df3ac94c95a148cb669ab748e3c7
COMPONENT_FMRI=         library/desktop/gdk-pixbuf
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

COMPONENT_FMRI.gdk-pixbuf-32 =		$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.gdk-pixbuf-32 =	$(COMPONENT_SUMMARY) (32-bit)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH = $(PATH.gnu)

# Enable all loaders
CONFIGURE_OPTIONS += -Dothers=enabled
# We prefer no builtin loaders, but we need to make png builtin because
# otherwise the build fails.
CONFIGURE_OPTIONS += -Dbuiltin_loaders=png
# Do not install tests
CONFIGURE_OPTIONS += -Dinstalled_tests=false

COMPONENT_POST_INSTALL_ACTION += LD_LIBRARY_PATH=$(PROTOUSRLIBDIR.$(BITS)) \
	$(PROTO_DIR)/$(CONFIGURE_BINDIR.$(BITS))/gdk-pixbuf-query-loaders \
	   $(PROTOUSRLIBDIR.$(BITS))/gdk-pixbuf-2.0/*/loaders/*.so | sed -e "s:$(PROTO_DIR)/*:/:" \
	   > $(PROTOUSRLIBDIR.$(BITS))/gdk-pixbuf-2.0/2.10.0/loaders.cache ;

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/gi-docgen
PYTHON_REQUIRED_PACKAGES += library/python/docutils
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)/32
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
