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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nose
COMPONENT_VERSION=	1.3.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://github.com/nose-devs/nose
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b40c2ff268beb85356ada25f626ca0dabc89705f31051649772cf00fc9510326
COMPONENT_ARCHIVE_URL=	http://pypi.python.org/packages/source/n/nose/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/nose

TPNO=			18083

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_ARGS =	selftest.py

# Used to automatically run the Python 2.6 nose tests even though there was
# an error found when running one of the Python 2.7 ones.
COMPONENT_TEST_ARGS +=	|| true

# Save an original copy of the test script to be able to edit it correctly
# for each version of Python and build the tests once.
COMPONENT_POST_UNPACK_ACTION += \
	($(CP) $(SOURCE_DIR)/selftest.py $(SOURCE_DIR)/selftest.py.orig ; \
	cd $(COMPONENT_TEST_DIR); $(COMPONENT_TEST_ENV_CMD) \
                $(COMPONENT_TEST_ENV) \
                $(COMPONENT_TEST_CMD) setup.py build_tests)

# We need to adjust the script that is used to run the tests, to pick the
# appropriate nose in the proto area depending upon which version of Python
# we are running the tests against.
COMPONENT_PRE_TEST_ACTION = \
	$(GSED) -e "s|'build', 'lib\*'|'..', 'build', 'prototype', '$(MACH)', 'usr', 'lib', 'python$(PYTHON_VERSION)', 'vendor-packages\*'|" \
		$(SOURCE_DIR)/selftest.py.orig > $(SOURCE_DIR)/selftest.py

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# Note that it is currently not feasible to add master test file(s) for this
# component because "chances are you will experience odd, intermittent and
# unexplainable failures and errors" when using the multiprocess plug. See:
# http://nose.readthedocs.org/en/latest/plugins/multiprocess.html
# CR #20470423 has been filed to investigate these failures.

test:		$(TEST_NO_ARCH)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
