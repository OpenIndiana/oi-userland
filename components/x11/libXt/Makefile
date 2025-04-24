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
# Copyright 2016 Aurelien Larcher
#

X11_CATEGORY=LIB
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libXt
COMPONENT_VERSION= 1.3.1
COMPONENT_SUMMARY= libXt - X Toolkit library
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:e0a774b33324f4d4c05b199ea45050f87206586d81655f8bef4dba434d931288
COMPONENT_FMRI=    x11/library/toolkit/libxt
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_ANITYA_ID=    1793

TEST_TARGET= $(TEST_64)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += -Wno-error=incompatible-pointer-types

# https://bugs.freedesktop.org/show_bug.cgi?id=6569
LD_B_DIRECT=

COMPONENT_PREP_ACTION= ( cd $(@D) && PATH="$(PATH)" autoreconf -f -i )

CPPFLAGS += -DGETVALUES_BUG -DNO_ALLOCA

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= LIB_MAN_SUFFIX=3xt

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
