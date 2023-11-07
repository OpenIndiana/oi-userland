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
# Copyright (c) 2015-2021 Jim Klimov
# Copyright (c) 2023 Niklas Poslovski
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ccache
COMPONENT_VERSION=      4.8.3
COMPONENT_SUMMARY=      ccache - cacher of GCC-compiled files to avoid doing the same job twice
COMPONENT_PROJECT_URL=  https://ccache.dev
COMPONENT_DOCUMENTATION_URL =	https://ccache.dev/documentation.html
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:e47374c810b248cfca3665ee1d86c7c763ffd68d9944bc422d9c1872611f2b11
COMPONENT_ARCHIVE_URL=  https://github.com/ccache/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/ccache
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_LICENSE=      GPLv3, murmurhash, papowell/jhweiss, PostgreSQL, Python, zlib
COMPONENT_LICENSE_FILE= LICENSE.adoc

include $(WS_MAKE_RULES)/common.mk

unexport SHELLOPTS

#COMPONENT_TEST_TRANSFORMS += '-e "s/ [0-9].[0-9][0-9] sec//" '
#COMPONENT_TEST_TRANSFORMS += '-e "s/ [0-9][0-9].[0-9][0-9] sec//" '
#COMPONENT_TEST_TRANSFORMS += '-e "s/ [0-9][0-9][0-9].[0-9][0-9] sec//" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += database/hiredis
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
