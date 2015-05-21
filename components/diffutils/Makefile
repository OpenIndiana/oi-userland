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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

COMPILER=		gnu

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		diffutils
COMPONENT_VERSION=	3.3
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/diffutils/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a25e89a8ab65fded1731e4186be1bb25cda967834b6df973599cdcd5abdfc19c
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/diffutils/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-diffutils

TPNO=			21995

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =		(cd $(@D) ; autoreconf -f)

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += system/library
