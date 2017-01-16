#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2015 Ken Mays. All Rights Reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libdrm
COMPONENT_VERSION=      2.4.71
COMPONENT_PROJECT_URL=  http://dri.freedesktop.org
COMPONENT_SUMMARY=      Userspace interface to kernel Direct Rendering Module services
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:c66287ddeee5f46ea8f8880b94b80acb3bbc33ba6321d17767eef145046df9b8
COMPONENT_ARCHIVE_URL=  http://dri.freedesktop.org/libdrm/$(COMPONENT_ARCHIVE) 
COMPONENT_FMRI= x11/library/libdrm
COMPONENT_CLASSIFICATION = System/X11
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = libdrm.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CPPFLAGS += "-I/usr/include/pixman-1"

CONFIGURE_LIBDIR.32 = /usr/lib/xorg
CONFIGURE_LIBDIR.64 = /usr/lib/xorg/$(MACH64)

CONFIGURE_OPTIONS+=      --disable-static
CONFIGURE_OPTIONS+=      --disable-valgrind
CONFIGURE_OPTIONS+=      --enable-cairo-tests
CONFIGURE_OPTIONS+=      --enable-libkms
CONFIGURE_OPTIONS+=      --enable-intel
CONFIGURE_OPTIONS+=      --enable-radeon
CONFIGURE_OPTIONS+=      --enable-amdgpu
CONFIGURE_OPTIONS+=      --disable-nouveau
CONFIGURE_OPTIONS+=      --enable-omap-experimental-api
CONFIGURE_OPTIONS+=      --enable-exynos-experimental-api
CONFIGURE_OPTIONS+=      --enable-freedreno
CONFIGURE_OPTIONS+=      --enable-freedreno-kgsl
CONFIGURE_OPTIONS+=      --enable-tegra-experimental-api
CONFIGURE_OPTIONS+=      --enable-etnaviv-experimental-api
CONFIGURE_OPTIONS+=      --enable-vc4

CONFIGURE_ENV+= CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV+= MISC_MAN_SUFFIX=7

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += system/library
