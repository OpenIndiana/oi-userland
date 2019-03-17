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
# Copyright (c) 2014, 2018, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

# Component uses ABI3 naming.
PYTHON3_SOABI=abi3

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cryptography
COMPONENT_VERSION=	2.1.4
COMPONENT_REVISION=	4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e4d967371c5b6b2e67855066471d844c5d52d210c36c28d49a8507b96e2c5291
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://cryptography.io/
COMPONENT_BUGDB=	python-mod/cryptography
COMPONENT_ANITYA_ID=	5532

PYTHON_VERSIONS = 2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

#
# The test suite requires several PyPI packages not in our distribution.
# Install them for all Pythons in $(PYTHON_VERSION) like this (replace
# Makefile variables, where appropriate; X and Y stand for Python minor
# and, respectively, major version):
#
#   pipX.Y install --user cryptography-vectors==$(COMPONENT_VERSION) iso8601 pretend pytest hypothesis pyasn1-modules
#
# Results for Python 2.7.16, 3.4.9, and 3.5.6 for 32-bit and 64-bit:
#
#   93184 passed, 4352 skipped in 308.30 seconds
#
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_TEST_CMD=	py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS=	tests

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += library/python/pytest-27
REQUIRED_PACKAGES += library/python/pytest-34
REQUIRED_PACKAGES += library/python/pytest-35
REQUIRED_PACKAGES += library/python/cffi
REQUIRED_PACKAGES += runtime/python-34
# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
