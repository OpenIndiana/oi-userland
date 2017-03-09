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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hg-git
COMPONENT_VERSION=	0.8.5
COMPONENT_PROJECT_URL=	http://hg-git.github.io/
COMPONENT_BUGDB=	python-mod/hg-git
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	http://bitbucket.org/durin42/$(COMPONENT_NAME)/get/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_ANITYA_ID=	1314

TPNO=			33779

PYTHON_VERSIONS=	$(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

UNPACK_DIR=		durin42-$(COMPONENT_NAME)-53d514c9c7e6
COMPONENT_POST_UNPACK_ACTION= ( $(MV) $(UNPACK_DIR) $(COMPONENT_SRC))

COMPONENT_TEST_DIR=	$(SOURCE_DIR)/tests
COMPONENT_TEST_ARGS=	run-tests.py --with-hg=$(HG)
COMPONENT_TEST_MASTER=	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ENV=	PATH=/usr/gnu/bin:/usr/bin

CLEAN_PATHS +=		$(COMPONENT_ARCHIVE)

build:		$(BUILD_NO_ARCH)
install:	$(INSTALL_NO_ARCH)
# until dulwich is generally available
test:		$(NO_TESTS)
system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)
