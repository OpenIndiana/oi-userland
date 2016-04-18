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
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Tk
# pkg does not like leading zeros, removed zero after dot.
COMPONENT_VERSION=	804.33
HUMAN_VERSION=		804.033
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	http://search.cpan.org/~srezic/Tk
COMPONENT_ARCHIVE_HASH=	\
    sha256:84756e9b07a2555c8eecf88e63d5cbbba9b1aa97b1e71a3d4aa524a7995a88ad
COMPONENT_ARCHIVE_URL=	http://search.cpan.org/CPAN/authors/id/S/SR/SREZIC/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	perl-mod/tk

TPNO=			22548

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/makemaker.mk

# This component loves openwin.
CONFIGURE_OPTIONS += X11INC=/usr/X11/include
CONFIGURE_OPTIONS += X11LIB=/usr/X11/lib/64

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_TARGETS = test

build:		$(BUILD_64)

install:	$(INSTALL_64)

# Tests work but require an X display and for some reason does not like
# our test harness.  Unable to connect to X display.
# 23107507 perl-tk tests fail to work inside the userland test framework
test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxft
