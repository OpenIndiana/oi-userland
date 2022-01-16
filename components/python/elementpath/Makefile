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
COMPONENT_VERSION=      2.4.0
COMPONENT_SUMMARY=		XPath 1.0/2.0 parsers and selectors for ElementTree and lxml
COMPONENT_PROJECT_URL=  https://pypi.org/project/elementpath/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5b6801b3be94d48d213beb7b8ebad96addb35c95fc6a9c062c80e033b4a32fe8
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_FMRI=			library/python/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=		MIT

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

# Note: Tests don't properly work yet.
COMPONENT_TEST_DIR=    $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD=    tox-3.9
COMPONENT_TEST_ARGS=

# Manually added test dependencies
REQUIRED_PACKAGES += library/python/tox-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
