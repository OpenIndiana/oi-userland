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

COMPONENT_NAME=		lesscpy
COMPONENT_VERSION=	0.9j
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fa01d435a1ab3abafba683519bdc7aca5e19399e96225e1a8bc1d660b566364d
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/robotis/Lesscpy
COMPONENT_BUGDB=	python-mod/lesscpy

# Depends on ply which is not Python 3 ready.
PYTHON_VERSIONS=	2.7 2.6

# convert the 'j' in COMPONENT_VERSION to 10
IPS_COMPONENT_VERSION = 0.9.10

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Author's name has non-ASCII characters.
COMPONENT_BUILD_ENV	+=	LC_ALL=en_US.UTF-8
COMPONENT_INSTALL_ENV	+=	LC_ALL=en_US.UTF-8

COMPONENT_POST_INSTALL_ACTION = \
         (cd $(PROTO_DIR)/usr/bin ; $(MV) -f lesscpy lesscpy-$(PYTHON_VERSION))

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
