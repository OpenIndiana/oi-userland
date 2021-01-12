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

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		py
COMPONENT_VERSION=	1.8.0
COMPONENT_FMRI=		library/python/py
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SUMMARY=	py - library with cross-python path, ini-parsing, io, code, log facilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:dc639b046a6e2cff5bbe40194ad65936d6ba360b52b3c3fe1d08a82dd50b5e53
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://bitbucket.org/hpk42/py
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS=	2.7 3.5 3.7 3.9


# Tests require the pytest package to be installed: circular dependency.
TEST_TARGET=  $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_ENV += LC_ALL=en_US.UTF-8
COMPONENT_TEST_DIR =	$(COMPONENT_SRC)/testing
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
