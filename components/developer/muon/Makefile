#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Vincent Torri
#
BUILD_BITS=64
BUILD_STYLE=meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           muon
COMPONENT_VERSION=        0.5.0
COMPONENT_SUMMARY=        muon is an implementation of the meson build system in c99
COMPONENT_PROJECT_URL=    https://github.com/muon-build/muon
COMPONENT_SRC=            $(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=    https://muon.build/releases/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=   sha256:24aa4d29ed272893f6e6d355b1ec4ef20647438454e88161bdb9defd7c6faf77
COMPONENT_FMRI=           developer/build/muon
COMPONENT_CLASSIFICATION= Development/Distribution Tools
COMPONENT_LICENSE=        GPLv3
COMPONENT_LICENSE_FILE=   LICENSES/GPL-3.0-only.txt

include $(WS_MAKE_RULES)/common.mk

PATH=                    $(PATH.gnu)

CONFIGURE_OPTIONS += --buildtype=release
CONFIGURE_OPTIONS += --strip

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += developer/build/pkgconf
