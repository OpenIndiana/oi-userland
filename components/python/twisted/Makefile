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

COMPONENT_NAME=		Twisted
COMPONENT_VERSION=	10.1.0
COMPONENT_PROJECT_URL=	http://twistedmatrix.com/trac/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:eda6e0e9e5ef6f6c19ab75bcb094f83a12ee25fe589fbcddf946e8a655c8070b
COMPONENT_ARCHIVE_URL=	http://twistedmatrix.com/Releases/$(COMPONENT_NAME)/10.1/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/twisted

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR= $(COMPONENT_SRC)
COMPONENT_TEST_CMD= $(@D)/scripts-2.6/trial twisted
COMPONENT_TEST_ARGS=""

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

# There are no automated tests yet, but the built-in unit tests can be run
# manually with:
#
# $ cd .../components/python/twisted/Twisted-10.1.0
# $ ../build/i86-2.6/scripts-2.6/trial twisted
# $ ../build/i86-2.7/scripts-2.7/trial twisted
#
test:           $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
