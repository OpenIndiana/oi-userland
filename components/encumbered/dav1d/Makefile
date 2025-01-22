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
# Copyright 2021 (c) Tim Mooney. All rights reserved.
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         dav1d
COMPONENT_VERSION=      1.5.1
COMPONENT_SUMMARY=      A fast, cross-platform AV1 decoder
COMPONENT_PROJECT_URL=  https://code.videolan.org/videolan/dav1d
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:fa635e2bdb25147b1384007c83e15de44c589582bb3b9a53fc1579cb9d74b695
COMPONENT_FMRI=         codec/dav1d
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=      BSD 2-Clause Simplified License
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

# We need XPG6MODE for clock_gettime():
CFLAGS += $(XPG6MODE)
CONFIGURE_OPTIONS += -Denable_asm=true

# build requirement
REQUIRED_PACKAGES += developer/assembler/nasm

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
