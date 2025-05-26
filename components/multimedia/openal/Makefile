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
# Copyright 2017 Gary Mills
# Copyright 2017 Alexander Pyhalov
# Copyright 2025 Klaus Ziegler
#

BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= openal
COMPONENT_VERSION= 1.23.1
COMPONENT_SUMMARY= OpenAL is a cross-platform 3D audio API
COMPONENT_PROJECT_URL= https://openal-soft.org/
COMPONENT_SRC= $(COMPONENT_NAME)-soft-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:dfddf3a1f61059853c625b7bb03de8433b455f2f79f89548cbcbd5edca3d4a4a
COMPONENT_ARCHIVE_URL= https://github.com/kcat/openal-soft/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/audio/openal
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

# this is need to statisfy pkgmogrify, see also 02-pkgmogrify.patch
COMPONENT_POST_UNPACK_ACTION= \
	$(MV) $(COMPONENT_SRC)/hrtf/Default\ HRTF.mhr $(COMPONENT_SRC)/hrtf/Default-HRTF.mhr

CMAKE_OPTIONS += -DCMAKE_POLICY_VERSION_MINIMUM=3.5

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
