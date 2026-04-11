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
# Copyright 2016 Alexander Pyhalov
#

X11_CATEGORY=LIB
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libXmu
COMPONENT_VERSION= 1.3.1
COMPONENT_SUMMARY= libXmu - miscellaneous utility functions for Xaw and Xt clients
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:81a99e94c4501e81c427cbaa4a11748b584933e94b7a156830c3621256857bc4
COMPONENT_FMRI=    x11/library/libxmu
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(TEST_64)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) && \
                          cd $(@D) && PATH="$(PATH)" autoreconf -f  -i )

CFLAGS += -I/usr/include/X11/xcms

CONFIGURE_OPTIONS += --without-lint
CONFIGURE_OPTIONS += --disable-lint-library

COMPONENT_BUILD_ARGS += V=1

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/toolkit/libxt
