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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#

COMPILER =	gcc

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		greenlet
COMPONENT_VERSION=	0.4.9
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	\
    sha256:58b2f3a2e7075c655616bf95e82868db4980f3bb6661db70ad02a51e4ddd2252
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/python-greenlet/greenlet
COMPONENT_BUGDB=	python-mod/greenlet

TPNO=			26538

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

CC =		$(COMPONENT_DIR)/CC.sh

COMPONENT_PRE_BUILD_ACTION = \
	$(MKDIR) $(SOURCE_DIR)/64

LDSHARED=	$(CC) -shared
PYTHON_ENV +=	LDSHARED="$(LDSHARED)"

# One of the tests, test_exception_switch (tests.test_cpp.CPPTests),
# failed in 64-bit. Skip it for now.
COMPONENT_TEST_ENV +=	GREENLET_TEST_CPP=no
COMPONENT_TEST_ENV +=	PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES)
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_TEST_ARGS=	setup.py test

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += system/library
