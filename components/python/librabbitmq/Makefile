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

COMPONENT_NAME=		librabbitmq
COMPONENT_VERSION=	1.0.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:645763262ad61df3feec618c3cbe1226710a364fca57256f61c53b0101abd880
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://github.com/celery/librabbitmq
COMPONENT_BUGDB=	python-mod/librabbitmq

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

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# librabbitmq tests fail to compile; more investigation is needed.
test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
