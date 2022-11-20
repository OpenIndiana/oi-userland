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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fs-uae
COMPONENT_VERSION=	3.1.66
COMPONENT_SUMMARY=	Accurate Amiga Emulation
COMPONENT_PROJECT_URL=	https://fs-uae.net/
COMPONENT_FMRI=		emulators/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://fs-uae.net/files/FS-UAE/Stable/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:606e1868b500413d69bd33bb469f8fd08d6c08988801f17b7dd022f3fbe23832
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	fs-uae.txt

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = mkdir $(SOURCE_DIR)/dist/solaris; cp -r files/* $(SOURCE_DIR)/dist/solaris; cd $(SOURCE_DIR); autoreconf -fi

LDFLAGS += -lsocket -lnsl

CONFIGURE_ENV += "LDFLAGS=$(LDFLAGS)"

CONFIGURE_OPTIONS += --disable-jit

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
