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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zope.interface
COMPONENT_VERSION=	4.3.2
COMPONENT_PROJECT_URL=	http://zope.org/Wikis/Interfaces/FrontPage
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:6a0e224a052e3ce27b3a7b1300a24747513f7a507217fcc2a4cb02eb92945cee
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_BUGDB=	python-mod/zope

TPNO=			32154

# Syntax issues: not Python 3 ready.
PYTHON_VERSIONS=	$(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_ARGS=	../runtests.sh
COMPONENT_TEST_CMD=	/bin/sh
COMPONENT_TEST_DIR=	$(SOURCE_DIR)
COMPONENT_TEST_ENV+=	PYTHON=$(PYTHON)

# Master test results are the same for all supported versions of Python, so
# override here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# The additional zope.interface specific set of transforms to be applied
# to the test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(Ran 1 test in\).*|\1|" ' \
	'-e "s|\(Ran .* tests in\).*|\1|" '

COMPONENT_SYSTEM_TEST_ARGS=	../runtests.sh
COMPONENT_SYSTEM_TEST_CMD=	/bin/sh
COMPONENT_SYSTEM_TEST_DIR=	$(SOURCE_DIR)
COMPONENT_SYSTEM_TEST_ENV+=	PYTHON=$(PYTHON)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TEST_32_and_64)

REQUIRED_PACKAGES += system/library
