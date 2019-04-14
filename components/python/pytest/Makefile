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
# Copyright (c) 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pytest
COMPONENT_VERSION=	4.6.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:8fc39199bdda3d9d025d3b1f4eb99a192c20828030ea7c9a0d2840721de7d347
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://pytest.org/latest/
COMPONENT_BUGDB=	python-mod/pytest

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_POST_INSTALL_ACTION = \
	$(CP) $(PROTO_DIR)/usr/bin/py.test $(PROTO_DIR)/usr/bin/py.test-$(PYTHON_VERSION); \
	$(CP) $(PROTO_DIR)/usr/bin/pytest  $(PROTO_DIR)/usr/bin/pytest-$(PYTHON_VERSION); \
	$(GSED) -i "1s|python.*|python${PYTHON_VERSION}|" $(PROTO_DIR)/usr/bin/py.test-$(PYTHON_VERSION); \
	$(GSED) -i "1s|python.*|python${PYTHON_VERSION}|" $(PROTO_DIR)/usr/bin/pytest-$(PYTHON_VERSION); \
	$(RM) $(PROTO_DIR)/usr/bin/pytest $(PROTO_DIR)/usr/bin/py.test;

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# Tests require the py package to be installed, and others, which are not in the distribution,
# to be installed by pipX.Y and included via $PYTHONPATH.
#
# Results:
#   [2.7] 32 failed, 2269 passed, 106 skipped, 11 xfailed, 1 warnings in 410.14 seconds
#   [3.4] 33 failed, 2261 passed, 113 skipped, 11 xfailed, 1 warnings in 445.52 seconds
#   [3.5] 32 failed, 2269 passed, 106 skipped, 11 xfailed, 1 warnings in 410.14 seconds
#     One PDB test case hangs, needs to be Ctr-C manually.
#
# And, most importantly, pytest needs itself for it's test suite to run correctly.
COMPONENT_TEST_ENV =	PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES):$$HOME/.local/lib/python$(PYTHON_VERSION)/site-packages
COMPONENT_TEST_DIR =	$(COMPONENT_SRC)
COMPONENT_TEST_CMD =	py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =	testing/

test:		$(TEST_NO_ARCH)

# Build dependencies
# py is required for tests to run
REQUIRED_PACKAGES += library/python/py-27
REQUIRED_PACKAGES += library/python/py-34
REQUIRED_PACKAGES += library/python/py-35
REQUIRED_PACKAGES += library/python/wcwidth

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-34
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
