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
# Copyright (c) 2013, 2020, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		requests
COMPONENT_VERSION=	2.22.0
COMPONENT_SUMMARY=	Python HTTP Requests for Humans
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:11e007a8a2aa0323f5a921e9e6a2d7e4e67d9877e85773fba9ba6419025cbeb4
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_PROJECT_URL=	https://python-requests.org/
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_FMRI=		library/python/$(COMPONENT_NAME)
COMPONENT_LICENSE= Apache 2

PYTHON_VERSIONS= 3.5

# Tests require access to AWS services & the Internet
TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-35
