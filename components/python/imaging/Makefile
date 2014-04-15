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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Imaging
COMPONENT_VERSION=	1.1.7
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.pythonware.com/products/pil/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:895bc7c2498c8e1f9b99938f1a40dc86b3f149741f105cf7c7bd2e0725405211
COMPONENT_ARCHIVE_URL=	http://effbot.org/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/pil

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

TEST_PYTHONPATH.32 = $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/PIL
TEST_PYTHONPATH.64 = $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/PIL:$(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/PIL/64

COMPONENT_TEST_DIR= $(COMPONENT_SRC)
COMPONENT_TEST_ARGS= ./selftest.py
COMPONENT_TEST_ENV= PYTHONPATH=$(TEST_PYTHONPATH.$(BITS))

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
