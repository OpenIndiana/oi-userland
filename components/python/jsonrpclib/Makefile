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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		jsonrpclib
COMPONENT_VERSION=	0.4.3
COMPONENT_PROJECT_URL=	https://github.com/tcalmant/jsonrpclib
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:242248e71fab1fb0c2c20502e6a8df7c990d314014423bb282482943b3afd3c7
COMPONENT_ARCHIVE_URL=https://github.com/tcalmant/jsonrpclib/archive/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	$(PYTHON_VERSIONS_ALL)

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_TEST_CMD= /usr/bin/nosetests
COMPONENT_TEST_ARGS = tests

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/enum-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
