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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		python-memcached
COMPONENT_VERSION=	1.53
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7ae92b948d9a53d8d522fed1551eeb191f25879e34d533a59e7736ffaf2a7c14
COMPONENT_ARCHIVE_URL=	https://github.com/linsomniac/$(COMPONENT_NAME)/archive/release-$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://github.com/linsomniac/python-memcached
COMPONENT_BUGDB=	python-mod/memcached

TPNO=			17839

# Syntax errors: not Python 3 ready
PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_POST_UNPACK_ACTION = \
	$(MV) python-memcached-release-1.53 \
	    $(COMPONENT_NAME)-$(COMPONENT_VERSION)

COMPONENT_TEST_ARGS=	test
COMPONENT_TEST_CMD=	$(MAKE)
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
# "make test" expects GNU Make as make(1)
COMPONENT_TEST_ENV=	PATH=/usr/gnu/bin:/usr/bin

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# tests require local, online svc:/application/database/memcached:default
test:		$(TEST_NO_ARCH)

REQUIRED_PACKAGES += runtime/python-27
