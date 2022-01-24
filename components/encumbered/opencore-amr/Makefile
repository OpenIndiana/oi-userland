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
# Copyright 2015 Alexander Pyhalov
#

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         opencore-amr
COMPONENT_VERSION=      0.1.5
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      OpenCORE AMR speech codec library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:2c006cb9d5f651bfb5e60156dbff6af3c9d35c7bbcc9015308c0aff1e14cd341
COMPONENT_ARCHIVE_URL=  \
	http://sourceforge.net/projects/opencore-amr/files/opencore-amr/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://opencore-amr.sourceforge.net/
COMPONENT_LICENSE=      APLv2.0
COMPONENT_CLASSIFICATION=System/Media
COMPONENT_FMRI=         codec/opencore-amr

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-compile-c
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
