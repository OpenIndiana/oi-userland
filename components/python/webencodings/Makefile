#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 erwinlem
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
USE_COMMON_TEST_MASTER=	no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         webencodings
COMPONENT_VERSION=      0.5.1
COMPONENT_SUMMARY=      Character encoding aliases for legacy web content
COMPONENT_PROJECT_URL=  https://github.com/SimonSapin/python-webencodings
COMPONENT_FMRI=         library/python/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_ARCHIVE_HASH= sha256:b36a1c245f2d304965eb4e0a82848379241dc04b865afcc4aab16748587e1923
COMPONENT_LICENSE=      Apache-2.0 

PYTHON_VERSIONS=    3.7 3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =	tests.py
COMPONENT_TEST_DIR =	$(SOURCE_DIR)/webencodings
COMPONENT_TEST_TRANSFORMS += '-e "s/ [0-9]*[0-9].[0-9][0-9]s/ X.XXs/" '
COMPONENT_TEST_TRANSFORMS += '-e "s/^Using --randomly-seed=[0-9]*/Using --randomly-seed=XXXXXXXXXX/" '

# Build dependencies
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
