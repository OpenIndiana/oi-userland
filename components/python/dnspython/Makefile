#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Friedrich Kink
#

# Component uses ABI3 naming.
PYTHON3_SOABI= abi3
BUILD_BITS= 64
BUILD_STYLE= setup.py
TEST_STYLE= pytest
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dnspython
COMPONENT_VERSION=	2.3.0
COMPONENT_SUMMARY=	Dnspython is a DNS toolkit for Python.
COMPONENT_PROJECT_URL=	https://www.dnspython.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:224e32b03eb46be70e12ef6d64e0be123a64e621ab4c0822ff6d450d52a540b9
COMPONENT_ARCHIVE_URL=	https://files.pythonhosted.org/packages/91/8b/522301c50ca1f78b09c2ca116ffb0fd797eadf6a76085d376c01f9dd3429/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/python/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

TEST_PYTHONPATH= $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages

COMPONENT_TEST_ENV=	PYTHONPATH=$(TEST_PYTHONPATH)
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD=	$(PYTHON)
COMPONENT_TEST_ARGS=	utest.py

# tests want to connect to google DNS server (8.8.8.8)
TEST_TARGET=		$(NO_TEST)

# Test dependencies
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/wheel

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
