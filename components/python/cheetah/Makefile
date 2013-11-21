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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Cheetah
COMPONENT_VERSION=	2.4.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:be308229f0c1e5e5af4f27d7ee06d90bb19e6af3059794e5fd536a6f29a9b550
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://www.cheetahtemplate.org/
COMPONENT_BUGDB=	python-mod/cheetah

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Needed to get around a broken /usr/lib/python2.7/config/Makefile
# See CR #16837431.
LD=$(CC)
LDSHARED=$(CC) -G
PYTHON_ENV += CC="$(CC)"
PYTHON_ENV += LDSHARED="$(LDSHARED)"
PYTHON_ENV += LD="$(LD)"
PYTHON_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += $(PYTHON_ENV)

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; \
	 $(MV) -f cheetah cheetah-$(PYTHON_VERSION) ; \
	 $(MV) -f cheetah-analyze cheetah-analyze-$(PYTHON_VERSION) ; \
	 $(MV) -f cheetah-compile cheetah-compile-$(PYTHON_VERSION))

COMPONENT_TEST_ARGS=	cheetah/Tests/Test.py
COMPONENT_TEST_DIR=	$(SOURCE_DIR)
COMPONENT_TEST_ENV=	PATH=$(PROTO_DIR)/usr/bin
COMPONENT_TEST_ENV +=	PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES.32)
COMPONENT_TEST_ENV +=	PYTHON_VERSION=$(PYTHON_VERSION)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
