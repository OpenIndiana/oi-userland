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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		argparse
COMPONENT_VERSION=	1.2.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ddaf4b0a618335a32b6664d4ae038a1de8fbada3b25033f9021510ed2b3941a4
COMPONENT_ARCHIVE_URL=	http://argparse.googlecode.com/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://code.google.com/p/argparse/
COMPONENT_BUGDB=	python-mod/argparse

# The argparse module was integrated into Python 2.7, so we should only deliver
# a 2.6 module.
PYTHON_VERSIONS = 2.6

include $(WS_MAKE_RULES)/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
