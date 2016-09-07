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
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xattr
COMPONENT_VERSION=	0.8.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:71d08712f78ed543215e4145779a336e42acb4003b97e16d493a680cf08f1d01
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://github.com/xattr/xattr
COMPONENT_BUGDB=	python-mod/xattr

TPNO=			30241

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

CFFI = $(WS_COMPONENTS)/python/cffi/build/prototype/$(MACH)/$(PYTHON_LIB)

COMPONENT_BUILD_ENV +=		PYTHONPATH=$(CFFI)
COMPONENT_INSTALL_ENV +=	PYTHONPATH=$(CFFI):$(PROTO_DIR)/$(PYTHON_LIB)
COMPONENT_TEST_ENV +=		PYTHONPATH=$(CFFI):$(PROTO_DIR)/$(PYTHON_LIB)
# The test suite wants to use some unicode filenames, which don't work in the C
# locale.
COMPONENT_TEST_ENV +=	LC_ALL=en_US.UTF-8
COMPONENT_TEST_DIR =	$(@D)/tests
COMPONENT_TEST_CMD =	$(PYTHON) setup.py
COMPONENT_TEST_ARGS =	test

COMPONENT_POST_INSTALL_ACTION += \
    (cd $(PROTO_DIR)/usr/bin; $(MV) xattr xattr-$(PYTHON_VERSION))

# Tests run under setuptools work very hard to run in the source directory
# itself, and will thus blow up with an VerificationError (wrong ELF class)
# when running 64-bit tests after 32-bit or vice-versa.  So copy the source off
# to a target-specific directory and run the tests.  Note that this will also
# rebuild the package, since it doesn't want to use what it should already be
# finding in PYTHONPATH.
COMPONENT_PRE_TEST_ACTION = $(CP) -r $(SOURCE_DIR) $(@D)/tests

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:	$(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-34
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/cffi-27
REQUIRED_PACKAGES += library/python/cffi-34
REQUIRED_PACKAGES += library/python/cffi-35
REQUIRED_PACKAGES += system/library
