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
include ../../../make-rules/shared-macros.mk

# librabbitmq will not configure with Studio compilers.  Despite
# passing LDFLAGS explicitly, the configure script in $SRC/clib is not
# able to find getaddrinfo in libsocket.  GCC builds with no issue.
COMPILER=		gcc

COMPONENT_NAME=		librabbitmq
COMPONENT_VERSION=	1.6.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:604a226b9fe3f9e439353702a731f2a39cf771882e68bca020cb224d9b990c49
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://github.com/celery/librabbitmq
COMPONENT_BUGDB=	python-mod/librabbitmq

TPNO=			28721

# This module is not Python 3 ready: syntax work needed.
PYTHON_VERSIONS=	$(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

PYTHON_ENV +=	LDSHARED="gcc -shared"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# librabbitmq tests fail to compile; more investigation is needed.
test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += system/library
