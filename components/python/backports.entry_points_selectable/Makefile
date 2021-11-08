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
# Copyright 2021 Andreas Wacknitz
#
BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	backports.entry_points_selectable
COMPONENT_VERSION= 	1.1.0
COMPONENT_SUMMARY=	Compatibility shim to ease adoption of importlib_metadata 3.6
COMPONENT_PROJECT_URL=	https://github.com/jaraco/backports.entry_points_selectable
COMPONENT_FMRI=	library/python/$(COMPONENT_NAME)
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:988468260ec1c196dab6ae1149260e2f5472c9110334e5d51adcb77867361f6a
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
