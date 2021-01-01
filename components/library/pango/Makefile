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
# Copyright 2019 Michal Nowak
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS=				32_and_64
BUILD_STYLE=			meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			pango
COMPONENT_VERSION_MAJOR=	1
COMPONENT_VERSION_MINOR=	48
COMPONENT_VERSION_MICRO=	0
COMPONENT_VERSION_DL=	$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)
COMPONENT_VERSION=		$(COMPONENT_VERSION_DL).$(COMPONENT_VERSION_MICRO)
COMPONENT_SUMMARY=		GNOME core text and font handling libraries
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:391f26f3341c2d7053e0fb26a956bd42360dadd825efe7088b1e9340a65e74e6
COMPONENT_ARCHIVE_URL=	https://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_DL)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.pango.org/
COMPONENT_FMRI=			library/desktop/pango
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS.32 += -Dintrospection=disabled

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_POST_INSTALL_ACTION.32 = ( $(RM) -fr $(PROTO_DIR)/etc/pango && $(MKDIR) $(PROTO_DIR)/etc/pango &&\
	$(ENV) LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib \
	$(PROTO_DIR)/usr/bin/pango-querymodules \
	  $(PROTO_DIR)/usr/lib/pango/*/modules/*.so   | sed -e "s:$(PROTO_DIR)::" \
	  > $(PROTO_DIR)/etc/pango/pango.modules )

COMPONENT_POST_INSTALL_ACTION.64 = ( $(RM) -fr $(PROTO_DIR)/etc/$(MACH64)/pango && $(MKDIR) $(PROTO_DIR)/etc/$(MACH64)/pango &&\
	$(ENV) LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib/$(MACH64) \
	$(PROTO_DIR)/usr/bin/$(MACH64)/pango-querymodules \
	  $(PROTO_DIR)/usr/lib/$(MACH64)/pango/*/modules/*.so | sed -e "s:$(PROTO_DIR)::" \
	  > $(PROTO_DIR)/etc/$(MACH64)/pango/pango.modules )

COMPONENT_POST_INSTALL_ACTION=$(COMPONENT_POST_INSTALL_ACTION.$(BITS))

# For test suites to pass
unexport SHELLOPTS

# We need to copy the markups otherwise the tests fail:
COMPONENT_PRE_TEST_ACTION = ( cp -R $(SOURCE_DIR)/tests/markups $(BUILD_DIR)/$(MACH$(BITS))/tests/ )

COMPONENT_TEST_TARGETS += ; cd tests; ./cxx-test; ./markup-parse; \
        ./test-font ; ./test-ot-tags; ./testattributes; \
        ./testboundaries; ./testcolor; ./testiter; ./testscript;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/input-method/library/libthai
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxrender
