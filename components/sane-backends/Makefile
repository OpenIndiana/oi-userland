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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		sane-backends
COMPONENT_VERSION=	1.0.19
COMPONENT_PROJECT_URL=	http://www.sane-project.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:13271a7eb4dc4aa6072162abbd78848e4faad32c468b9b44e7f95cde96a4e17e
COMPONENT_ARCHIVE_URL=	ftp://ftp2.sane-project.org/pub/sane/old-versions/sane-backends-1.0.19/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libsane

TPNO=			8865

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Fix 64-bit linking via compiler.
LDFLAGS += $(CC_BITS)

CONFIGURE_OPTIONS +=	--disable-locking
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)

# We only deliver 64-bit binaries and in /usr/bin, /usr/sbin.
COMPONENT_POST_INSTALL_ACTION.32 += \
	$(GSED) -i \
		-e 's|$(USRBINDIR)/$(MACH32)|$(USRBINDIR)|' \
		-e 's|$(USRSBINDIR)/$(MACH32)|$(USRSBINDIR)|' \
		$(PROTOUSRBINDIR)/$(MACH32)/sane-config;

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/usb/libusb
