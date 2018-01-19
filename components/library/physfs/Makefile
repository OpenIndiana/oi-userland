#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	physfs
COMPONENT_VERSION=	2.0.3
COMPONENT_FMRI=	library/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	PhysicsFS is a library to provide abstract access to various archives and limit write-access scope
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
  sha256:ca862097c0fb451f2cacd286194d071289342c107b6fe69079c079883ff66b69
COMPONENT_ARCHIVE_URL=	\
  http://icculus.org/physfs/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://icculus.org/physfs/
COMPONENT_CLASSIFICATION=	System/Libraries
# LGPL is pulled by 7z/lzma support, otherwise PhysicsFS is zlib-licensed
COMPONENT_LICENSE=	ZLIB,LGPL
COMPONENT_LICENSE_FILE=	LICENSE.txt

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

CXXFLAGS+=$(CXXFLAGS.$(BITS))
CFLAGS+=$(CFLAGS.$(BITS))

CMAKE_OPTIONS+=	-D PHYSFS_BUILD_STATIC=OFF
CMAKE_OPTIONS+=	-D PHYSFS_BUILD_SHARED=ON

# Use a definitive list of what we want to deliver
# (NOTE: dependency pkgs must be present for build)
CMAKE_OPTIONS+=	-D PHYSFS_ARCHIVE_ZIP=ON
CMAKE_OPTIONS+=	-D PHYSFS_ARCHIVE_7Z=ON
CMAKE_OPTIONS+=	-D PHYSFS_ARCHIVE_GRP=ON
CMAKE_OPTIONS+=	-D PHYSFS_ARCHIVE_WAD=ON
CMAKE_OPTIONS+=	-D PHYSFS_ARCHIVE_HOG=ON
CMAKE_OPTIONS+=	-D PHYSFS_ARCHIVE_MVL=ON
CMAKE_OPTIONS+=	-D PHYSFS_ARCHIVE_QPAK=ON

# PHYSFS_HAVE_CDROM_SUPPORT detection requires mntent.h or sys/ucred.h
# We apply a patch that tries to implement the support with our headers
CMAKE_OPTIONS+=	-D PHYSFS_HAVE_CDROM_SUPPORT=ON

# We want proper threading, but no particular preference for test programs
# or choice of zlib, readline, etc. (see end of CMakeLists.txt in source)
CMAKE_OPTIONS+=	-D PHYSFS_HAVE_THREAD_SUPPORT=ON

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
