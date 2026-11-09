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
# Copyright 2022 Till Wegmueller
#

BUILD_BITS=64 # for binaries or 32_and_64 for libraries
USE_PARALLEL_BUILD=	yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fs-uae
COMPONENT_VERSION=	3.2.35
COMPONENT_SUMMARY=	Accurate Amiga Emulation
COMPONENT_PROJECT_URL=	https://fs-uae.net/
COMPONENT_FMRI=		emulators/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://github.com/FrodeSolheim/fs-uae/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:f3d3cb8d3df34b0b0125c45a5a3e187ff71050be5dc8455cc4505c0380269117
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	fs-uae.txt

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

# The patches change configure.ac and Makefile.am
COMPONENT_PREP_ACTION = ( cd $(@D) && PATH="$(PATH)" $(AUTORECONF) -fi )

# The 68k JIT compiler (x86-64); patches/illumos-build.patch makes it build
# on illumos.
CONFIGURE_OPTIONS += --enable-jit

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += library/video/libmpeg2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
