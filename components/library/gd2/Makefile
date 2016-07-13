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
COMPONENT_VERSION_1=	2.1.1
COMPONENT_SRC_NAME_1=	gd
COMPONENT_SRC_1=	libgd-$(COMPONENT_SRC_NAME_1)-$(COMPONENT_VERSION_1)
# ...aka http://libgd.github.io/ nowadays
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_NAME_1)-$(COMPONENT_VERSION_1).tar.gz
COMPONENT_ARCHIVE_HASH_1=	\
    sha256:a68c69d2fe3eaab9db63b1c4d391dd549c26d3b47bfba484d5ed2d433c55d4d8
COMPONENT_ARCHIVE_URL_1=	https://github.com/libgd/libgd/archive/$(COMPONENT_ARCHIVE_1)

# Base variables are needed for packaging automagic
COMPONENT_ARCHIVE_URL=	$(COMPONENT_ARCHIVE_URL_1)
COMPONENT_SRC=	$(COMPONENT_SRC_1)
COMPONENT_REVISION=	1
COMPONENT_VERSION=	$(COMPONENT_VERSION_1)
COMPONENT_PROJECT_URL=	http://www.libgd.org/
COMPONENT_BUGDB=	library/gd2

#PATCH_EACH_ARCHIVE=1

# For now, we want to continue to provide the libgd.so's from version
# 2.0.35 that was available for a very long time as the only one.
# Original source is additionally patched with *.patch_2 files.
COMPONENT_VERSION_2=	2.0.35
COMPONENT_SRC_NAME_2=	gd
COMPONENT_SRC_2=	$(COMPONENT_SRC_NAME_2)-$(COMPONENT_VERSION_2)
COMPONENT_ARCHIVE_2=	$(COMPONENT_SRC_2).tar.bz2
COMPONENT_ARCHIVE_HASH_2=	\
    sha256:bf222490749d2a9a9ac3593b01eb55aed98461ff81202414707f61b42aa300f9
COMPONENT_ARCHIVE_URL_2=	http://pkgs.fedoraproject.org/repo/pkgs/gd/$(COMPONENT_ARCHIVE_2)/6c6c3dbb7bf079e0bb5fbbfd3bb8a71c/$(COMPONENT_ARCHIVE_2)
SOURCE_DIR_2=	$(COMPONENT_DIR)/$(COMPONENT_SRC_2)

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

CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_INCLUDEDIR)/gd2
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--disable-rpath
CONFIGURE_OPTIONS +=	--with-x
CONFIGURE_OPTIONS +=	--with-pic

$(BUILD_DIR_32_1)/.configured:	CONFIGURE_OPTIONS+=--with-vpx

COMPONENT_PREP_ACTION =	(cd $(SOURCE_DIR) && autoreconf -if && \
	cd $(SOURCE_DIR_2) && autoreconf -if )

COMPONENT_TEST_CMD = \
	cmake -DBUILD_TEST=1 .; \
	(cd $(@D)/tests; gmake); \
	ctest .
COMPONENT_TEST_TARGETS =

COMPONENT_PRE_CONFIGURE_ACTION_2 = \
	($(CLONEY) $(SOURCE_DIR_2) $(@D))

BUILD_DIR_32_2 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_2)-$(MACH32)
BUILD_DIR_64_2 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_2)-$(MACH64)

$(BUILD_DIR_32_2)/.configured:	CONFIGURE_SCRIPT=$(SOURCE_DIR_2)/configure
$(BUILD_DIR_32_2)/.configured:	COMPONENT_PRE_CONFIGURE_ACTION=$(COMPONENT_PRE_CONFIGURE_ACTION_2)
$(BUILD_DIR_32_2)/.configured:	BITS=32

$(BUILD_DIR_64_2)/.configured:	CONFIGURE_SCRIPT=$(SOURCE_DIR_2)/configure
$(BUILD_DIR_64_2)/.configured:	COMPONENT_PRE_CONFIGURE_ACTION=$(COMPONENT_PRE_CONFIGURE_ACTION_2)
$(BUILD_DIR_64_2)/.configured:	BITS=64

BUILD_32 +=	$(BUILD_DIR_32_2)/.built
BUILD_64 +=	$(BUILD_DIR_64_2)/.built

INSTALL_32 +=	$(BUILD_DIR_32_2)/.installed
INSTALL_64 +=	$(BUILD_DIR_64_2)/.installed

# install the old version first
$(BUILD_DIR_32)/.installed:     $(BUILD_DIR_32_2)/.installed
$(BUILD_DIR_64)/.installed:     $(BUILD_DIR_64_2)/.installed

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
