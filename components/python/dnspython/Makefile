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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dnspython
COMPONENT_VERSION=	2.2.1
COMPONENT_SUMMARY=	Dnspython is a DNS toolkit for Python.
COMPONENT_PROJECT_URL=	https://www.dnspython.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0f7569a4a6ff151958b64304071d370daa3243d15941a7beedf0c9fe5105603e
COMPONENT_ARCHIVE_URL=	https://files.pythonhosted.org/packages/99/fb/e7cd35bba24295ad41abfdff30f6b4c271fd6ac70d20132fa503c3e768e0/$(COMPONENT_ARCHIVE)
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
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
REQUIRED_PACKAGES += library/python/pytest-cov-37
REQUIRED_PACKAGES += library/python/pytest-cov-39
REQUIRED_PACKAGES += library/python/wheel-37
REQUIRED_PACKAGES += library/python/wheel-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
