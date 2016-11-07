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

# NOTE: This component delivers several versions of the library for
# backwards compatibility with both packaged and end-user-built code
COMPONENT_NAME=		gd2
COMPONENT_SRC_NAME=	gd
COMPONENT_SUMMARY=	The GD2 Graphics Draw Library
COMPONENT_DESCRIPTION=	GD - An open source code library for the dynamic creation of images by programmers
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_PROJECT_URL=	http://www.libgd.org/
COMPONENT_FMRI=		library/gd
COMPONENT_LICENSE=	GD2 License
COMPONENT_LICENSE_FILE=	gd2.license

# The current version, its patch-files have patch_1 suffix
# Also note that different releases had different filename patterns
COMPONENT_VERSION_1=	2.2.3
COMPONENT_SRC_1=	libgd-$(COMPONENT_VERSION_1)
# ...aka http://libgd.github.io/ nowadays
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.xz
COMPONENT_ARCHIVE_HASH_1=	\
    sha256:746b6cbd6769a22ff3ba6f5756f3512a769bd4cdf4695dff17f4867f25fa7d3c
COMPONENT_ARCHIVE_URL_1=	https://github.com/libgd/libgd/releases/download/$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION_1)/$(COMPONENT_ARCHIVE_1)

# Previous release, considerably patched for CVEs so it has no known security
# difference from 2.2.3 ;)
COMPONENT_VERSION_2=	2.1.1
COMPONENT_SRC_2=	libgd-$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION_2)
# ...aka http://libgd.github.io/ nowadays
COMPONENT_ARCHIVE_2=	$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION_2).tar.gz
COMPONENT_ARCHIVE_HASH_2=	\
    sha256:a68c69d2fe3eaab9db63b1c4d391dd549c26d3b47bfba484d5ed2d433c55d4d8
COMPONENT_ARCHIVE_URL_2=	https://github.com/libgd/libgd/archive/$(COMPONENT_ARCHIVE_2)

# For now, we want to continue to provide the libgd.so's from version
# 2.0.35 that was available for a very long time as the only one.
# Original source is additionally patched with *.patch_3 files.
# NOTE: This is currently built but not packaged, waiting to backport CVE patches
COMPONENT_VERSION_3=	2.0.35
COMPONENT_SRC_3=	$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION_3)
COMPONENT_ARCHIVE_3=	$(COMPONENT_SRC_3).tar.bz2
COMPONENT_ARCHIVE_HASH_3=	\
    sha256:bf222490749d2a9a9ac3593b01eb55aed98461ff81202414707f61b42aa300f9
COMPONENT_ARCHIVE_URL_3=	http://pkgs.fedoraproject.org/repo/pkgs/gd/$(COMPONENT_ARCHIVE_3)/6c6c3dbb7bf079e0bb5fbbfd3bb8a71c/$(COMPONENT_ARCHIVE_3)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

PATCH_LEVEL = 0

CFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_LARGEFILES)
LINT_FLAGS +=	-I$(SOURCE_DIR)/src

# Needed for "gmake test" to work.
# Common for both variants, as done below
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
	(cd $(@D) && ./bootstrap.sh)

# 2.0.35 did not have an autoconfig script
COMPONENT_PREP_ACTION_3 = \
	(cd $(@D) && autoreconf -if)

COMPONENT_TEST_CMD = \
	cmake -DBUILD_TEST=1 .; \
	(cd $(@D)/tests; gmake); \
	ctest .
COMPONENT_TEST_TARGETS =

CONFIGURE_ENV +=	CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_INCLUDEDIR)/gd2
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--disable-rpath
CONFIGURE_OPTIONS +=	--with-x
CONFIGURE_OPTIONS +=	--with-pic

#######################################
# Unique stuff for the newest version
# Enable this for the new version explicitly (to require installation of pkg)
# NOTE: Current builds do not take advantage of "liq" aka "libimagequant"
# (part of pngquant2) because they are not packaged with "oi-userland" so far.
$(BUILD_DIR_32_1)/.configured:	CONFIGURE_OPTIONS+=--with-webp
$(BUILD_DIR_64_1)/.configured:	CONFIGURE_OPTIONS+=--with-webp
$(BUILD_DIR_32_1)/.configured:	CONFIGURE_OPTIONS+=--with-iconv
$(BUILD_DIR_64_1)/.configured:	CONFIGURE_OPTIONS+=--with-iconv
$(BUILD_DIR_32_1)/.configured:	CONFIGURE_OPTIONS+=--with-vpx
$(BUILD_DIR_64_1)/.configured:	CONFIGURE_OPTIONS+=--with-vpx

# Rename the installed linted libraries
$(BUILD_DIR_32_1)/%.ln $(BUILD_DIR_64_1)/%.ln:	LINT_FLAGS+=-I$(SOURCE_DIR_1)/src

$(PROTOUSRLIBDIR)/llib-lgd-$(COMPONENT_VERSION_1).ln: $(BUILD_DIR_32_1)/llib-lgd.ln
	$(INSTALL) -c $< $@

$(PROTOUSRLIBDIR64)/llib-lgd-$(COMPONENT_VERSION_1).ln: $(BUILD_DIR_64_1)/llib-lgd.ln
	$(INSTALL) -c $< $@

#######################################
# Similarly for the next-newest version
$(BUILD_DIR_32_2)/.configured:	CONFIGURE_OPTIONS+=--with-vpx
$(BUILD_DIR_64_2)/.configured:	CONFIGURE_OPTIONS+=--with-vpx

# Rename the installed linted libraries
$(BUILD_DIR_32_2)/%.ln $(BUILD_DIR_64_2)/%.ln:	LINT_FLAGS+=-I$(SOURCE_DIR_2)/src

$(PROTOUSRLIBDIR)/llib-lgd-$(COMPONENT_VERSION_2).ln: $(BUILD_DIR_32_2)/llib-lgd.ln
	$(INSTALL) -c $< $@

$(PROTOUSRLIBDIR64)/llib-lgd-$(COMPONENT_VERSION_2).ln: $(BUILD_DIR_64_2)/llib-lgd.ln
	$(INSTALL) -c $< $@

#######################################
# Stuff for the older version; note it was earlier delivered without libvpx -
# so we keep it this way

# For now waiting on CVE backports to gd-2.0.* so not building
$(BUILD_DIR_32_3)/.built $(BUILD_DIR_64_3)/.built $(BUILD_DIR_32_3)/.installed $(BUILD_DIR_64_3)/.installed :
	@echo "Skipping $@"

# Rename the installed linted libraries
$(BUILD_DIR_32_3)/%.ln $(BUILD_DIR_64_3)/%.ln:	LINT_FLAGS+=-I$(SOURCE_DIR_3)

$(PROTOUSRLIBDIR)/llib-lgd-$(COMPONENT_VERSION_3).ln: $(BUILD_DIR_32_3)/llib-lgd.ln
	$(INSTALL) -c $< $@

$(PROTOUSRLIBDIR64)/llib-lgd-$(COMPONENT_VERSION_3).ln: $(BUILD_DIR_64_3)/llib-lgd.ln
	$(INSTALL) -c $< $@

#######################################
# Ensure installation order
# install the old versions first
$(BUILD_DIR_32_1)/.installed:     $(BUILD_DIR_32_2)/.installed $(BUILD_DIR_32_3)/.installed
$(BUILD_DIR_64_1)/.installed:     $(BUILD_DIR_64_2)/.installed $(BUILD_DIR_64_3)/.installed

# install linted-libs in order so they do not conflict for e.g. parallel builds
# note they must not be part of '.installed' target - they depend on it instead
$(PROTOUSRLIBDIR)/llib-lgd-$(COMPONENT_VERSION_1).ln: $(PROTOUSRLIBDIR)/llib-lgd-$(COMPONENT_VERSION_2).ln
$(PROTOUSRLIBDIR64)/llib-lgd-$(COMPONENT_VERSION_1).ln: $(PROTOUSRLIBDIR64)/llib-lgd-$(COMPONENT_VERSION_2).ln

# For now waiting on CVE backports to gd-2.0.* so not building
#$(PROTOUSRLIBDIR)/llib-lgd-$(COMPONENT_VERSION_2).ln: $(PROTOUSRLIBDIR)/llib-lgd-$(COMPONENT_VERSION_3).ln
#$(PROTOUSRLIBDIR64)/llib-lgd-$(COMPONENT_VERSION_2).ln: $(PROTOUSRLIBDIR64)/llib-lgd-$(COMPONENT_VERSION_3).ln

# Standard targets
build:		$(BUILD_32_and_64)

# This should pull *.ln for other versions via dependencies above
install:	$(INSTALL_32_and_64) \
	$(PROTOUSRLIBDIR)/llib-lgd-$(COMPONENT_VERSION_1).ln \
	$(PROTOUSRLIBDIR64)/llib-lgd-$(COMPONENT_VERSION_1).ln

# gdimageline_aa fails
test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/video/libvpx
REQUIRED_PACKAGES += library/video/libwebp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libxpm
