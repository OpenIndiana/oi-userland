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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pixz
COMPONENT_VERSION=	1.0.6
COMPONENT_PROJECT_URL=	http://github.com/vasi/pixz/
COMPONENT_ARCHIVE_HASH=	\
    sha256:c54a406dddc6c2226779aeb4b5d5b5649c1d3787b39794fbae218f7535a1af63
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	7490

TPNO=			27449

SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

PKG_PROTO_DIRS += $(BUILD_DIR_64)

# Needed to make the tests work, now we use configure.mk not justmake.mk.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Userland default includes -mt which links with libthread which we don't need.
studio_MT =

# pixz's src/Makefile hard-codes some gcc-only flags in pixz_CFLAGS.
# Here we exclude the gcc-only parts, so we can build with Studio.
# PTHREAD_CFLAGS is defined in the pixz .../src/Makefile.
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += pixz_CFLAGS="$(PTHREAD_CFLAGS)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(CC_BITS)"

# Create a small testball to use with the test script.
COMPONENT_PRE_TEST_ACTION = \
	(cd $(@D)/src; tar cvf pixz-test-tarball.tar  *.c *.o)
COMPONENT_PRE_SYSTEM_TEST_ACTION = \
	(cd $(@D)/src; tar cvf pixz-test-tarball.tar  *.c *.o)

COMPONENT_TEST_TRANSFORMS += \
	'-e "/^real/d" ' \
	'-e "/^user/d" ' \
	'-e "/^sys/d" '

COMPONENT_TEST_ENV =		PATH=$(GNUBIN):$(PATH)
COMPONENT_TEST_CMD =		$(SOURCE_DIR)/test.sh
COMPONENT_TEST_ARGS =		src/pixz-test-tarball.tar pixz.c
COMPONENT_TEST_TARGETS =

COMPONENT_SYSTEM_TEST_ENV =	PATH=$(GNUBIN):$(PATH)
COMPONENT_SYSTEM_TEST_ENV +=	PIXZ_BIN=$(USRBINDIR)/pixz
COMPONENT_SYSTEM_TEST_CMD =	$(SOURCE_DIR)/test.sh
COMPONENT_SYSTEM_TEST_ARGS =	src/pixz-test-tarball.tar pixz.c
COMPONENT_SYSTEM_TEST_TARGETS =

REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += system/library/math
