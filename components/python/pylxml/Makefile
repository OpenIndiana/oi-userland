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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lxml
COMPONENT_VERSION=	2.3.3
COMPONENT_PROJECT_URL=	http://lxml.de/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2a3ca34f63b062ee8e059ca2460ac18040ec9622f0a31e143383f0db944ceb36
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/$(COMPONENT_ARCHIVE)

# disable optimization to prevent the Studio compilers from spinning
studio_OPT.i386.32 =
studio_OPT.i386.64 =

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

# build modules PIC (needed for Python 2.7)
CFLAGS += $(CC_PIC)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(BUILD_32_and_64)
		cd $(SOURCE_DIR) && $(PYTHON) selftest.py
		cd $(SOURCE_DIR) && $(PYTHON) selftest2.py

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
