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
# Copyright 2017 Gary Mills
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 32_and_64
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyOpenSSL
COMPONENT_VERSION=	19.0.0
COMPONENT_SUMMARY=	Python interface to the OpenSSL library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:aeca66338f6de19d1aa46ed634c3b9ae519a64b458f8468aec688e7e3c20f200
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_PROJECT_URL=  https://pyopenssl.org/
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	Apache2

PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)

# We miss the flaky and pretend packages that are required for the tests:
TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/^\. lib/p" ' \
        '-e "/^\. tests/p" ' \
        '-e "/^s tests/p" ' \
        '-e "/^F tests/p" '

# Testing directly inside the build directory prevents ELFCLASS errors (because
# both 32bit and 64bit versions of Python 2.7 have their own directory and
# cached versions of 32/64 bit precompiled .so files are thus not a problem.)
COMPONENT_PRE_TEST_ACTION = $(CP) -r $(COMPONENT_SRC)/tests $(@D)
COMPONENT_TEST_DIR =	$(@D)
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =	--disable-warnings

# Some tests require unicode characters, otherwise ~17 tests will fail
COMPONENT_TEST_ENV += TZ=UTC LC_ALL=en_US.UTF-8

# Manually added test dependencies
#REQUIRED_PACKAGES += library/python/flaky
REQUIRED_PACKAGES += library/python/nose
#REQUIRED_PACKAGES += library/python/pretend

# Manually added dependencies
REQUIRED_PACKAGES += library/security/openssl

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
