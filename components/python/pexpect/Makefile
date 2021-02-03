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
# Copyright 2018 Alexander Pyhalov
# Copyright 2021 Nona Hansel
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
PYTHON3_ONLY=yes
USE_COMMON_TEST_MASTER=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         pexpect
COMPONENT_VERSION=      4.8.0
COMPONENT_PROJECT_URL=  https://github.com/pexpect/pexpect
COMPONENT_FMRI=         library/python/pexpect
COMPONENT_SUMMARY=	Pure Python Expect-like module
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:fc65a43959d153d0114afe13997d439c22823a27cefceb5ff35c2178c6784c0c
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=      ISC
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

#XXX: Test suite hangs with Python 3.5
COMPONENT_TEST_DIR =	$(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =	--verbose
COMPONENT_TEST_ENV +=	PATH=$(GNUBIN):$(PATH)

COMPONENT_TEST_TRANSFORMS += \
	'-n -e "/::.*FAILED/p"' \
	'-e "/::.*ERROR/p"'

# Test dependencies
REQUIRED_PACKAGES += library/python/ptyprocess
# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
