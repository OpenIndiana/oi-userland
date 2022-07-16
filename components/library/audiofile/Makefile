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
# Copyright 2016 Alexander Pyhalov
#

BUILD_STYLE=configure
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         audiofile
COMPONENT_VERSION=      0.2.7
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      Library that provides APIs for accessing various audio file formats
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:a61c4036c2600a645843f16bec4be166093a9df5f15b02c85291213aa9cf15a2
# Tarballs were moved to Github and repackaged
COMPONENT_ARCHIVE_URL=  \
	http://dlc.openindiana.org/oi-userland/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.68k.org/~michael/audiofile/
COMPONENT_FMRI=         library/audio/audiofile
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE_FILE= audiofile.license
COMPONENT_LICENSE=      LGPLv2,GPLv2

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
