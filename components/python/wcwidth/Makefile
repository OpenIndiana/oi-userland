# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Adam Stevko
#

BUILD_STYLE=setup.py
BUILD_BITS=NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         wcwidth
COMPONENT_VERSION=      0.2.5
COMPONENT_SUMMARY=      Measures number of Terminal column cells of wide-character codes
COMPONENT_PROJECT_URL=  https://github.com/jquast/wcwidth
COMPONENT_FMRI=         library/python/wcwidth
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_ARCHIVE_HASH= sha256:c4d647b99872929fdb7bdcaa4fbe7f01413ed3d98077df798530e5b04f116c83
COMPONENT_LICENSE=      MIT

PYTHON_VERSIONS=	$(PYTHON_VERSIONS_ALL)

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
