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
COMPONENT_VERSION=	0.4.0
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	https://github.com/tcalmant/jsonrpclib
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:dfe491c11ede2d2177625c1938aea91b36d01831d0676aa031d7131311fe51d5
COMPONENT_ARCHIVE_URL=https://github.com/tcalmant/jsonrpclib/archive/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/jsonrpclib

PYTHON_VERSIONS=	2.7 3.5

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_TEST_CMD= /usr/bin/nosetests
COMPONENT_TEST_ARGS = tests

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/enum-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
