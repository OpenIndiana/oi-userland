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

COMPONENT_NAME=		openusb
COMPONENT_VERSION=	1.0.1
COMPONENT_SRC_NAME=	libopenusb
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://openusb.sourceforge.net/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:031098c376f16f6030c4dbd553266e107b39d1f7b3fc366f8f7fd412d3d7c3ad
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/openusb/files/libopenusb/libopenusb%201.0.1/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	library/libopenusb

TPNO=			8843

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

PATCH_LEVEL = 1

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D)/src; $(MAKE) install-sunos-backend)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
