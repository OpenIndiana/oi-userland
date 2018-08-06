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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gdk-pixbuf
COMPONENT_VERSION= 2.36.12
COMPONENT_SUMMARY= GNOME gdk-pixbuf
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:fff85cf48223ab60e3c3c8318e2087131b590fd6f1737e42cb3759a3b427a334
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.36/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://gitlab.gnome.org/GNOME/gdk-pixbuf
COMPONENT_FMRI=	library/desktop/gdk-pixbuf

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && aclocal  -I m4 && \
				libtoolize --force --copy&& \
				autoheader && \
				automake -a -f -c --gnu && \
				autoconf )

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

CONFIGURE_OPTIONS.32 += --sysconfdir=/etc
CONFIGURE_OPTIONS.64 += --sysconfdir=/etc/$(MACH64)
CONFIGURE_OPTIONS += --with-x11

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_POST_INSTALL_ACTION.32 = ( LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib \
	$(PROTO_DIR)/usr/bin/gdk-pixbuf-query-loaders \
	   $(PROTO_DIR)/usr/lib/gdk-pixbuf-2.0/*/loaders/*.so	| sed -e "s:$(PROTO_DIR)::" \
	   > $(PROTO_DIR)/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache )

COMPONENT_POST_INSTALL_ACTION.64 = ( LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib/$(MACH64) \
	$(PROTO_DIR)/usr/bin/$(MACH64)/gdk-pixbuf-query-loaders \
	   $(PROTO_DIR)/usr/lib/$(MACH64)/gdk-pixbuf-2.0/*/loaders/*.so	| sed -e "s:$(PROTO_DIR)::" \
	   > $(PROTO_DIR)/usr/lib/$(MACH64)/gdk-pixbuf-2.0/2.10.0/loaders.cache )

COMPONENT_POST_INSTALL_ACTION=$(COMPONENT_POST_INSTALL_ACTION.$(BITS))

COMPONENT_BUILD_ENV += CC="$(CC)"

# This file is required by a jpeg test, but missing from the release tarball
COMPONENT_PRE_TEST_ACTION+= ( $(CP) $(COMPONENT_DIR)/files/bug753605-atsize.jpg $(SOURCE_DIR)/tests/ )

# Fix tests
COMPONENT_TEST_ENV += PATH=$(PATH.gnu)
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += '-ne "/^SKIP/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^PASS/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^FAIL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^XPASS/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^XFAIL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^ERROR/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^\# /p" '

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
