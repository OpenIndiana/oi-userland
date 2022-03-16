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
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         elementpath
COMPONENT_VERSION=      2.5.0
COMPONENT_SUMMARY=		XPath 1.0/2.0 parsers and selectors for ElementTree and lxml
COMPONENT_PROJECT_URL=  https://pypi.org/project/elementpath/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3a27aaf3399929fccda013899cb76d3ff111734abf4281e5f9d3721ba0b9ffa3
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_FMRI=			library/python/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=		MIT

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

# Note: Tests don't properly work yet.
TEST_VERSION=	$(subst .,,$(PYTHON_VERSION))
COMPONENT_TEST_DIR=    $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD=    tox -e py$(TEST_VERSION)
COMPONENT_TEST_ARGS=

# Manually added test dependencies
REQUIRED_PACKAGES += library/python/tox

# Manually added dependencies
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
