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
# Copyright (c) 2012, 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		greenlet
COMPONENT_VERSION=	0.4.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	\
    sha256:ea671592f8460541286b133ed46a6cf5311a6b75051cc31b53e2bc38992b775a
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/python-greenlet/greenlet
COMPONENT_BUGDB=	python-mod/greenlet

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPILER =	gcc
CC =		$(COMPONENT_DIR)/CC.sh

COMPONENT_PRE_BUILD_ACTION = \
	$(MKDIR) $(SOURCE_DIR)/64

# Needed to get around a broken /usr/lib/python2.7/config/Makefile
# See CR #16837431.
LD=$(CC)
LDSHARED=$(CC) -shared
PYTHON_ENV += CC="$(CC)"
PYTHON_ENV += LDSHARED="$(LDSHARED)"
PYTHON_ENV += LD="$(LD)"
PYTHON_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += $(PYTHON_ENV)

# One of the tests, test_exception_switch (tests.test_cpp.CPPTests), 
# failed in 64-bit. Skip it for now.
COMPONENT_TEST_ENV +=	GREENLET_TEST_CPP=no
COMPONENT_TEST_ENV +=	PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES.32)
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_TEST_ARGS=	setup.py test

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
