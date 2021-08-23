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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright 2020 OmniOS Community Edition (OmniOSce) Association.
#

BUILD_BITS=			64
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		python-rapidjson
COMPONENT_VERSION=	1.4
COMPONENT_SUMMARY=	JSON (Java Script Object Notation) encoder/decoder for Python
COMPONENT_PROJECT_URL=	https://pypi.org/project/python-rapidjson/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:018c20d3983cccfdc9cfed64407d4ba861ef3d64fe324a486f7130431afdefa7
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/rapidjson
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=      MIT

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

# Tests require the pytest package to be installed, our pytest is too old, so
# we get some errors
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD=	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS=

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
