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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		python-dateutil
COMPONENT_VERSION=	2.5.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1408fdb07c6a1fa9997567ce3fcee6a337b39a503d80699e0f213de4aa4b32ed
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://dateutil.readthedocs.org
COMPONENT_BUGDB=	python-mod/dateutil

TPNO=			28610

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# Run the tests in the build directory so as not to touch the source directory.
# Because they're not copied over during the build, we do that now.
COMPONENT_PRE_TEST_ACTION = \
	$(CP) -r $(COMPONENT_SRC)/dateutil/test $(@D)
COMPONENT_TEST_DIR = $(@D)
COMPONENT_TEST_CMD = py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS = --result-log=$(COMPONENT_TEST_OUTPUT)
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

test:		$(TEST_NO_ARCH)

system-test:    $(NO_TESTS)
