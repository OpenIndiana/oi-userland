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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2016 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

# The current version, its patch-files have patch_1 suffix
COMPONENT_NAME=		gd2
COMPONENT_VERSION=	2.1.1
COMPONENT_SRC_NAME=	gd
COMPONENT_SRC=	libgd-$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
# ...aka http://libgd.github.io/ nowadays
COMPONENT_ARCHIVE=	$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a68c69d2fe3eaab9db63b1c4d391dd549c26d3b47bfba484d5ed2d433c55d4d8
COMPONENT_ARCHIVE_URL=	https://github.com/libgd/libgd/archive/$(COMPONENT_ARCHIVE)
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	http://www.libgd.org/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

PATCH_LEVEL = 0

CFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_LARGEFILES)
LINT_FLAGS +=	-I$(SOURCE_DIR)/src

# Needed for "gmake test" to work.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV +=	CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_INCLUDEROOTDIR)/$(COMPONENT_NAME)
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--disable-rpath
CONFIGURE_OPTIONS +=	--with-x
CONFIGURE_OPTIONS +=	--with-pic
CONFIGURE_OPTIONS +=	--with-vpx

COMPONENT_PREP_ACTION =	(cd $(SOURCE_DIR) && autoreconf -if )

COMPONENT_TEST_CMD = \
	cmake -DBUILD_TEST=1 .; \
	(cd $(@D)/tests; gmake); \
	ctest .
COMPONENT_TEST_TARGETS =

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# gdimageline_aa fails
test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/video/libvpx
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libxpm
