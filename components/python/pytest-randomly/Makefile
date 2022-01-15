#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
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

COMPONENT_NAME=		pytest-randomly
COMPONENT_VERSION=	3.11.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Pytest plugin to randomly order tests and control random.seed 
COMPONENT_PROJECT_URL=	https://github.com/pytest-dev/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:9f013b8c1923130f3d0a286fde56e1fc52cfb3547b8eedf2765c460cee979c7f
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=		library/python/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS= 3.7 3.9

# This package doesn't have any tests
TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
