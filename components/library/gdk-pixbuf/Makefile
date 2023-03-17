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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE = meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gdk-pixbuf
COMPONENT_VERSION=      2.42.10
COMPONENT_SUMMARY=      GNOME gdk-pixbuf
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:ee9b6c75d13ba096907a2e3c6b27b61bcd17f5c7ebeab5a5b439d2f2e39fe44b
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/2.42/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://gitlab.gnome.org/GNOME/gdk-pixbuf
COMPONENT_FMRI=         library/desktop/gdk-pixbuf
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)
CONFIGURE_ENV += CPPFLAGS="$(JPEG_CPPFLAGS)"

CONFIGURE_OPTIONS += -Dinstalled_tests=false

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_POST_INSTALL_ACTION = ( LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib/$(MACH64) \
	$(PROTO_DIR)/usr/bin/$(MACH64)/gdk-pixbuf-query-loaders \
	   $(PROTO_DIR)/usr/lib/$(MACH64)/gdk-pixbuf-2.0/*/loaders/*.so	| sed -e "s:$(PROTO_DIR)::" \
	   > $(PROTO_DIR)/usr/lib/$(MACH64)/gdk-pixbuf-2.0/2.10.0/loaders.cache )

# Fix tests
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += ' -e "s/[0-9]*\.[0-9]*s/X.XXs/" '

# Manually added dependencies
PYTHON_REQUIRED_PACKAGES += library/python/gi-docgen
PYTHON_REQUIRED_PACKAGES += library/python/docutils

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
