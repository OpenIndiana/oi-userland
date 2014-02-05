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
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		oslo.config
COMPONENT_VERSION=	1.2.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e4ccf489159f0c2b1932ea282f7663daada0a7f8309edc4c34904605a98cf9f2
COMPONENT_ARCHIVE_URL=	http://tarballs.openstack.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	python-mod/osol.config

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_POST_INSTALL_ACTION += \
        ($(TOUCH) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/oslo/__init__.py; \
         $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES))

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# Tests require:
# fixtures, mox, nose, nose-exclude, testtools, coverage, sphinx
# some of which haven't been integrated yet
test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
