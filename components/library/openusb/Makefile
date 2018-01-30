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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openusb
COMPONENT_VERSION=	1.0.1
COMPONENT_REVISION=	1
COMPONENT_FMRI=         system/library/usb/openusb
COMPONENT_SUMMARY=      A USB device management library
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC_NAME=	libopenusb
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://openusb.sourceforge.net/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:031098c376f16f6030c4dbd553266e107b39d1f7b3fc366f8f7fd412d3d7c3ad
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/openusb/files/libopenusb/libopenusb%20$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=      LGPLv2.1, BSD 

CONFIGURE_FIX_LIBTOOL_RPATH = no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) && libtoolize -f && autoreconf -fi)

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

CFLAGS+= -std=gnu89

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D)/src; $(MAKE) install-sunos-backend)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
