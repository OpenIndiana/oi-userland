#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gd2
COMPONENT_VERSION=      2.0.35
COMPONENT_SRC_NAME=	gd
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.libgd.org/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
# this is the hash of the payload because it appears to be re-compressed
# periodically causing it to have a new hash value.
COMPONENT_ARCHIVE_HASH= \
    sha256:44bd0819b64a2341fb800abbe99f23c7f6388327c71e1f5bd5ed7874a8cc0e49
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/gd2

TPNO=			8786

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig
PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig

PATCH_LEVEL = 0

CFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_LARGEFILES)

# Needed for "gmake test" to work.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH_$(BITS))"

CONFIGURE_OPTIONS  +=           --includedir=$(CONFIGURE_INCLUDEDIR)/gd2
CONFIGURE_OPTIONS  +=           --disable-static
CONFIGURE_OPTIONS  +=           --disable-rpath
CONFIGURE_OPTIONS  +=           --with-x
CONFIGURE_OPTIONS  +=           --with-pic

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -if)

COMPONENT_TEST_CMD = \
	cmake -DBUILD_TEST=1 .; \
	(cd $(@D)/tests; gmake); \
	ctest .
COMPONENT_TEST_TARGETS =
COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(^.*32 Test.*Passed\).*|\1|" ' \
	'-e "s|\(^.*32 Test.*Failed\).*|\1|" ' \
	'-e "s|\(^Total Test time (real) =\).*|\1|" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test:	$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)



REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxpm
