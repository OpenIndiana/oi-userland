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
# Copyright (c) 2021 Nona Hansel 
# Copyright (c) 2021 Andreas Wacknitz
#

BUILD_BITS=			NO_ARCH
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pycparser
COMPONENT_VERSION=	2.21
COMPONENT_SUMMARY=	Complete C99 parser in pure Python
COMPONENT_DESCRIPTION=	pycparser is a parser for the C language, written in pure Python. \
						It is a module designed to be easily integrated into applications that need to parse C source code.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e644fdec12f7872f86c58ff790da456218b10f863970249516d60a5eaca77206
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/eliben/pycparser
COMPONENT_FMRI=		library/python/pycparser
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	BSD

PYTHON_VERSIONS=	$(PYTHON_ALL_VERSIONS)
# Tests can only be run for python 3 versions as we miss some necessary packages for python-2.7.
#PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR=	$(SOURCE_DIR)/tests
COMPONENT_TEST_CMD=	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS=

$(SOURCE_DIR)/pycparser/ply/lex.py: $(SOURCE_DIR)/.prep

$(BUILD_DIR)/license.ply: $(SOURCE_DIR)/pycparser/ply/lex.py
	nawk '/^# Copyright / {p=1} /^# ---/ {p=0} p == 1 {print substr($$0, 3)}' $< > $@

# common targets
install:	$(INSTALL_NO_ARCH) $(BUILD_DIR)/license.ply

# Due to a packaging oversight, pycparser modifies c_ast.py after
# the compilation is done, resulting in a stale pyc file.
COMPONENT_POST_INSTALL_ACTION += \
	$(PYTHON) -m compileall $(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES_BASE)/pycparser/c_ast.py

# Manually added test dependencies
REQUIRED_PACKAGES += library/python/flaky-35
REQUIRED_PACKAGES += library/python/flaky-37
REQUIRED_PACKAGES += library/python/flaky-39
REQUIRED_PACKAGES += library/python/hypothesis-35
REQUIRED_PACKAGES += library/python/hypothesis-37
REQUIRED_PACKAGES += library/python/hypothesis-39
REQUIRED_PACKAGES += library/python/pluggy-35
REQUIRED_PACKAGES += library/python/pluggy-37
REQUIRED_PACKAGES += library/python/pluggy-39
REQUIRED_PACKAGES += library/python/py-35
REQUIRED_PACKAGES += library/python/py-37
REQUIRED_PACKAGES += library/python/py-39
REQUIRED_PACKAGES += library/python/pytest-35
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
REQUIRED_PACKAGES += library/python/pytest-benchmark-35
REQUIRED_PACKAGES += library/python/pytest-benchmark-37
REQUIRED_PACKAGES += library/python/pytest-benchmark-39
REQUIRED_PACKAGES += library/python/pytest-reporter-35
REQUIRED_PACKAGES += library/python/pytest-reporter-37
REQUIRED_PACKAGES += library/python/pytest-reporter-39
REQUIRED_PACKAGES += library/python/sortedcontainers-35
REQUIRED_PACKAGES += library/python/sortedcontainers-37
REQUIRED_PACKAGES += library/python/sortedcontainers-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
