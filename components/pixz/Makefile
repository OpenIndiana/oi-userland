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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pixz
COMPONENT_VERSION=	1.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://github.com/vasi/pixz/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:912c60de88f7eca2e1c6fe13eec5371f723018dca933796c47cd50bf6a349fc9
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)archive/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/pixz

TPNO=			11623

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_PROTO_DIRS += $(BUILD_DIR_64)
PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

# Userland default includes -mt which links with libthread which we don't need.
studio_MT =

# pixz's Makefile hard-codes some gcc-only flags in MYCFLAGS and MYLDFLAGS,
# then appends CFLAGS & LDFLAGS to each.  Here we include their preset values
# minus the gcc-only parts, so we can build with Studio.
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += MYCFLAGS='$(patsubst %,-I%/include,$(LIBPREFIX)) $(OPT)'
COMPONENT_BUILD_ARGS += MYLDFLAGS='$(patsubst %,-L%/lib,$(LIBPREFIX)) $(OPT)'
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(CC_BITS)"

# Create a small testball to use with the test script.
COMPONENT_PRE_TEST_ACTION = \
	(cd $(@D); tar cvf pixz-test-tarball.tar  *.c *.o)
COMPONENT_PRE_SYSTEM_TEST_ACTION = \
	(cd $(@D); tar cvf pixz-test-tarball.tar  *.c *.o)

COMPONENT_TEST_TRANSFORMS += \
	'-e "/^real/d" ' \
	'-e "/^user/d" ' \
	'-e "/^sys/d" '

COMPONENT_TEST_ENV =		PATH=$(GNUBIN):$(PATH)
COMPONENT_TEST_CMD =		$(SOURCE_DIR)/test.sh
COMPONENT_TEST_ARGS =		pixz-test-tarball.tar pixz.c
COMPONENT_TEST_TARGETS =

COMPONENT_SYSTEM_TEST_ENV =	PATH=$(GNUBIN):$(PATH)
COMPONENT_SYSTEM_TEST_ENV +=	PIXZ_BIN=/usr/bin/pixz
COMPONENT_SYSTEM_TEST_CMD =	$(SOURCE_DIR)/test.sh
COMPONENT_SYSTEM_TEST_ARGS =	pixz-test-tarball.tar pixz.c
COMPONENT_SYSTEM_TEST_TARGETS =

ASLR_MODE = $(ASLR_ENABLE)

build:		$(BUILD_64)

install:	$(BUILD_64)

test:		$(TEST_64)

system-test:    build $(SYSTEM_TEST_64)


REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += system/library
