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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		simplejson
COMPONENT_VERSION=	3.6.5
COMPONENT_PROJECT_URL=	http://undefined.org/python/#simplejson
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:2a3189f79d1c7b8a2149a0e783c0b4217fad9b30a6e7d60450f2553dc2c0e57e
COMPONENT_ARCHIVE_URL=	http://pypi.python.org/packages/source/s/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/simplejson
COMPONENT_ANITYA_ID=	4026

TPNO=			21749

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

ifeq ($(OS_VERSION),5.11)
OLD_DESKTOP_BUILD=	0.5.11,5.11-0.175.2.0.0.20.0
else
OLD_DESKTOP_BUILD=	5.12-5.12.0.0.0.14.0
endif

PKG_MACROS +=		OLD_DESKTOP_BUILD=$(OLD_DESKTOP_BUILD)

COMPONENT_TEST_DIR= $(COMPONENT_SRC)/$(COMPONENT_NAME)/tests
COMPONENT_TEST_CMD= /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS= -v

# The additional simplejson specific set of transforms to be applied
# to the test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^_.*/d" ' \
	'-e "/^=.*/d" ' \
	'-e "/SOURCE_DIR.*/d" ' \
	'-e "/^ *$$/d" ' \
	'-e "/^platform sunos5 .*/d" ' \
	'-e "/^plugins.*/d" ' \
	'-e "/pep8/d" ' \
	'-e "/pyflakes/d" '

COMPONENT_SYSTEM_TEST_DIR= $(COMPONENT_SRC)/$(COMPONENT_NAME)/tests
COMPONENT_SYSTEM_TEST_CMD= /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_SYSTEM_TEST_ARGS= -v
COMPONENT_SYSTEM_TEST_ENV =

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TEST_32_and_64)

REQUIRED_PACKAGES += system/library
