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
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyOpenSSL
COMPONENT_VERSION=	19.0.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:aeca66338f6de19d1aa46ed634c3b9ae519a64b458f8468aec688e7e3c20f200
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_PROJECT_URL=  https://pyopenssl.org/
COMPONENT_FMRI=		library/python/pyopenssl

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# In tests/test_crypto.py::FunctionTests::test_dump_certificate, the serial number line
# outputs the same hex as the key, so this is a false error.
#
# Install dependencies locally:
#   pipX.Y install --user -I pathlib2 atomicwrites attrs pluggy py flaky pretend funcsigs
#
# Results:
#   [2.7/32] 1 failed, 496 passed, 2 skipped, 17 warnings (F: TestFunction.test_dump_certificate)
#   [3.4/32] 1 failed, 483 passed, 15 skipped, 20 warnings (F: TestFunction.test_dump_certificate)
#   [2.7/64] 498 passed, 1 skipped, 17 warnings
#   [3.4/64] 485 passed, 14 skipped, 20 warnings
#   [3.5/64] 485 passed, 14 skipped, 20 warnings

COMPONENT_TEST_DIR = $(COMPONENT_SRC)
COMPONENT_TEST_ENV = PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES.32):$$HOME/.local/lib/python$(PYTHON_VERSION)/site-packages
# Some tests require unicode characters, otherwise ~17 tests will fail
COMPONENT_TEST_ENV += LC_ALL=en_US.UTF-8
# https://github.com/pyca/pyopenssl/issues/684#issuecomment-347242747
COMPONENT_TEST_ENV += TZ=UTC
COMPONENT_TEST_CMD = $(PYTHON.$(PYTHON_VERSION).$(BITS)) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS= -v

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
