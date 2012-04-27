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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		logilab-astng
COMPONENT_VERSION=	0.19.0
COMPONENT_PROJECT_URL=	http://www.logilab.org/project/logilab-astng/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e1b4d209e2a66b20c9e1adff2c30e3b19ea2a43226da3c7dff5c39747ca6e113
COMPONENT_ARCHIVE_URL=	http://ftp.logilab.org/pub/astng/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk
include ../../make-rules/setup.py.mk

# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)

# COMPONENT_TEST_CMD = ./fulltest.sh
# COMPONENT_TEST_ARGS = $(PYTHON_VERSION)

# No runnable tests; the existing tests are missing a runtests.py
# file, which isn't fixed until logilab-ast version 0.20.1.
# When logilab-astng is updated, uncomment the above COMPONENT_TEST*
# variables and change $(NO_TESTS) below to $(TEST_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
