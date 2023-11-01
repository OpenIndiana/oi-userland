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

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libvisual
COMPONENT_VERSION =	0.4.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Libvisual provides a convenient API for writing visualization plugins
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:2aa5967c5c9522c8d7ab9bd9246c77a582c1aaf4f2b3f06493dbe3066f00380a
COMPONENT_ARCHIVE_URL= 	https://github.com/Libvisual/libvisual/releases/download/libvisual-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://libvisual.org/
COMPONENT_FMRI = library/desktop/libvisual
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -Wl,-M$(COMPONENT_DIR)/files/map.remove_all

COMPONENT_PREP_ACTION= ( \
	cd $(@D)  && \
	PATH="$(PATH)" libtoolize --copy --force && \
	aclocal -I m4 &&\
	automake -c -f -a &&\
	autoconf )

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --enable-shared=yes
CONFIGURE_OPTIONS += --enable-static=no

# Use bitness specific lvconfig.h
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTOUSRDIR)/include/libvisual-0.4/libvisual/lvconfig.h $(PROTOUSRDIR)/include/libvisual-0.4/libvisual/lvconfig-$(BITS).h ; \
	$(INSTALL) $(COMPONENT_DIR)/files/lvconfig.h $(PROTOUSRDIR)/include/libvisual-0.4/libvisual ;

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR32) ;

# Build dependencies
REQUIRED_PACKAGES += library/glib2

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
