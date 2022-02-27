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
COMPONENT_VERSION=	1.11.0
COMPONENT_FMRI=		library/python/py
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SUMMARY=	py - library with cross-python path, ini-parsing, io, code, log facilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:51c75c4126074b472f746a24399ad32f6053d1b34b68d2fa41e558e6f4a98719
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://py.readthedocs.io/en/latest/
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS= $(PYTHON_ALL_VERSIONS)

# Tests are failing
include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR= $(SOURCE_DIR)
PYV= $(subst .,,$(PYTHON_VERSION))
COMPONENT_TEST_CMD= tox -e py$(PYV)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Manually added build dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += library/python/setuptools_scm-27
REQUIRED_PACKAGES += library/python/setuptools_scm-35
REQUIRED_PACKAGES += library/python/setuptools_scm-37
REQUIRED_PACKAGES += library/python/setuptools_scm-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
