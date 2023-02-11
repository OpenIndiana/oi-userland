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
# Copyright 2023 Andreas Wacknitz
# Copyright 2023 Friedrich Kink
#

BUILD_STYLE=	justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= netpbm
COMPONENT_VERSION= 10.73.42
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Netpbm is a toolkit for manipulation of graphic images, including conversion of images between a variety of different formats.
COMPONENT_PROJECT_URL= https://netpbm.sourceforge.net/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= sha256:f1ddaa753d189aa7760a75265b6f7ab96eeedac3e2493ef57227824d058d528c
COMPONENT_ARCHIVE_URL= https://sourceforge.net/projects/$(COMPONENT_NAME)/files/super_stable/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI= library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	GPL,BSD,MIT,BSD
COMPONENT_LICENSE_FILE= doc/copyright_summary

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_BUILD_ACTION = ( \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
	$(MKDIR) $(PROTO_DIR); \
	$(GSED) -i -e 's/MACH64/$(MACH64)/' files/config.mk; \
	$(CP) files/config.mk $(@D)/config.mk; \
	)

# build with the distribution preferred libjpeg implementation
CFLAGS   +=  $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS +=  $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  +=  $(JPEG_LDFLAGS)

COMPONENT_INSTALL_ARGS=		package
COMPONENT_INSTALL_TARGETS=	pkgdir=$(PROTO_DIR)/usr

COMPONENT_TEST_ENV += -i PATH=$(PATH.gnu)
COMPONENT_TEST_TARGETS=	check-tree
COMPONENT_TEST_TRANSFORMS= \
        '-n ' \
	'-e "/=======$$/p"' \
	'-e "/All tests done./p"' \
	'-e "/SUCCESS/p"' \
	'-e "/TESTABLE/p"' \
	'-e "/FAILURE/p"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
