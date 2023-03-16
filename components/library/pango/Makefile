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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         pango
COMPONENT_VERSION_MAJOR=	1
COMPONENT_VERSION_MINOR=	50
COMPONENT_VERSION_MICRO=	14
COMPONENT_REVISION=	1
COMPONENT_VERSION_DL=	$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)
COMPONENT_VERSION=      $(COMPONENT_VERSION_DL).$(COMPONENT_VERSION_MICRO)
COMPONENT_SUMMARY=      GNOME core text and font handling libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:1d67f205bfc318c27a29cfdfb6828568df566795df0cb51d2189cde7f2d581e8
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_DL)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.pango.org/
COMPONENT_FMRI=         library/desktop/pango
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_POST_INSTALL_ACTION = ( $(RM) -fr $(PROTO_DIR)/etc/$(MACH64)/pango && $(MKDIR) $(PROTO_DIR)/etc/$(MACH64)/pango &&\
	$(ENV) LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib/$(MACH64) \
	$(PROTO_DIR)/usr/bin/$(MACH64)/pango-querymodules \
	  $(PROTO_DIR)/usr/lib/$(MACH64)/pango/*/modules/*.so | sed -e "s:$(PROTO_DIR)::" \
	  > $(PROTO_DIR)/etc/$(MACH64)/pango/pango.modules )

# For test suites to pass
unexport SHELLOPTS

# cp boundaries.utf8 to tests directory in the build area
COMPONENT_PRE_TEST_ACTION += cp $(SOURCE_DIR)/tests/boundaries.utf8 \
      $(BUILD_DIR_$(BITS))/tests/
COMPONENT_TEST_TARGETS += ; cd tests; ./cxx-test; ./markup-parse; \
        ./test-break; ./test-converage; ./test-font ; ./test-ot-tags; \
        ./testboundaries; ./testcolor; ./testiter; ./testscript; \
    ./test-ellipsize; ./test-harfbuzz; ./test-itemize; ./test-layout; \
	./test-pangocairo-threads; ./test-shape; ./testmisc; ./testattributes;
COMPONENT_TEST_TRANSFORMS += '-e "s/      [0-9].[0-9][0-9]s//" '
COMPONENT_TEST_TRANSFORMS += '-e "s/      [0-9][0-9].[0-9][0-9]s//" '
COMPONENT_TEST_TRANSFORMS += \
		'-e "s/[0-9]*\:[0-9]*\:[0-9]*\.[0-9]*//" ' \
		'-e "s/test-layout\:[0-9]*/test-layout/" ' \
        '-n ' \
    	'-e "/Failures/d" ' \
        '-e "/Ok/p" ' \
        '-e "/Fail/p" ' \
        '-e "/Pass/p" ' \
        '-e "/Skipped/p" '

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
