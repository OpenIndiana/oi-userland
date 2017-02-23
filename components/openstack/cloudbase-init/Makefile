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
# Copyright (c) 2014, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cloudbase-init
COMPONENT_VERSION=	0.9.9
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0385c905952132ce944c821ea4f57ccffd660db7965ca8a62f28600939e659c1
COMPONENT_ANITYA_ID=	13227

COMPONENT_ARCHIVE_URL=	\
    https://github.com/openstack/cloudbase-init/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://github.com/stackforge/cloudbase-init
COMPONENT_BUGDB=	service/cloudbase-init

TPNO=			26420

ifneq ($(BUILD_TYPE), evaluation)
BUILD_STYLE= setup.py
endif

# FOSS eval upgrade instructions lead to maintenance state; just skip.
# On S12, the same problem if the pkg is installed, but it's not on the
# default install list for S12.  If the S12 issue gets fixed, we can drop
# the following line and thus remove this from the do-not-publish list.
include $(WS_MAKE_RULES)/no-evaluation.mk

# Upstream only supports 3.3 from the Python 3 series
PYTHON_VERSIONS=	$(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)
PKG_MACROS +=		PYV=$(shell echo $(PYTHON_VERSIONS) | tr -d .)

# Copy the PKG-INFO file to the build root
COMPONENT_PRE_BUILD_ACTION = \
    $(CP) $(COMPONENT_DIR)/PKG-INFO $(SOURCE_DIR)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# Tests require testr which is not integrated
test:		$(NO_TESTS)

REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
