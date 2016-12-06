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

#
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openusb
COMPONENT_VERSION=	1.1.11
COMPONENT_SRC_NAME=	libopenusb
COMPONENT_PROJECT_URL=	http://openusb.sourceforge.net/
COMPONENT_ARCHIVE_HASH=	\
    sha256:434242e758155aba6e4ddd28460dc9a2565c44bb8861a35ceaf7a6bbcae4aa1e
COMPONENT_ARCHIVE_URL= https://sourceforge.net/projects/openusb/files/libopenusb/libopenusb-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download	
COMPONENT_BUGDB=	library/libopenusb

TPNO=			32726

include $(WS_MAKE_RULES)/common.mk

# keep traditional GNU semantics for inline functions so we don't lose
# openusb_le{16|32}_to_cpu
CFLAGS.gcc += -fgnu89-inline

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D)/src; $(MAKE) install-sunos-backend)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/hal
REQUIRED_PACKAGES += system/io/usb
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
