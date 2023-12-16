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
# Copyright 2020, 2021 Andreas Wacknitz
#

BUILD_BITS= 64
BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         pango
COMPONENT_MJR_VERSION=	1.51
COMPONENT_VERSION=      $(COMPONENT_MJR_VERSION).1
COMPONENT_SUMMARY=      GNOME core text and font handling libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:4530d79350a4663b1dee3401ad64c0d41aee08833452b318220d1f355cf31f42
COMPONENT_ARCHIVE_URL=  https://gitlab.gnome.org/GNOME/pango/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.pango.org/
COMPONENT_FMRI=         library/desktop/pango
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += -Dinstall-tests=true

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_POST_INSTALL_ACTION.64 = ( $(RM) -fr $(PROTO_DIR)/etc/$(MACH64)/pango && $(MKDIR) $(PROTO_DIR)/etc/$(MACH64)/pango &&\
	$(ENV) LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib/$(MACH64) \
	$(PROTO_DIR)/usr/bin/$(MACH64)/pango-querymodules \
	  $(PROTO_DIR)/usr/lib/$(MACH64)/pango/*/modules/*.so | sed -e "s:$(PROTO_DIR)::" \
	  > $(PROTO_DIR)/etc/$(MACH64)/pango/pango.modules )

COMPONENT_POST_INSTALL_ACTION=$(COMPONENT_POST_INSTALL_ACTION.$(BITS))

# For test suites to pass
unexport SHELLOPTS

# cp boundaries.utf8 to tests directory in the build area
COMPONENT_PRE_TEST_ACTION += \
	cp $(SOURCE_DIR)/tests/boundaries.utf8 $(BUILD_DIR_$(BITS))/tests/

COMPONENT_TEST_TARGETS += ; cd tests; ./cxx-test; ./markup-parse; \
	./test-break; ./test-converage; ./test-font ; ./test-ot-tags; \
	./testboundaries; ./testcolor; ./testiter; ./testscript; \
	./test-ellipsize; ./test-harfbuzz; ./test-itemize; ./test-layout; \
	./test-pangocairo-threads; ./test-shape; ./testmisc; ./testattributes;

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/      [0-9].[0-9][0-9]s//" ' \
	'-e "s/      [0-9][0-9].[0-9][0-9]s//" ' \
	'-e "s/[0-9]*\:[0-9]*\:[0-9]*\.[0-9]*//" ' \
	'-e "s/test-layout\:[0-9]*/test-layout/" '

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
