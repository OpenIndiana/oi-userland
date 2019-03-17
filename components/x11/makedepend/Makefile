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
# Copyright 2015 Aurelien Larcher
#
BUILD_BITS=64

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           makedepend
COMPONENT_VERSION=        1.0.6
COMPONENT_FMRI=           developer/build/makedepend
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_SUMMARY=  makedepend - makefile dependency generation utility
COMPONENT_PROJECT_URL=    $(XORG_PROJECT_URL)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:d558a52e8017d984ee59596a9582c8d699a1962391b632bec3bb6804bf4d501c
COMPONENT_ARCHIVE_URL=    $(XORG_UTIL_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=        MIT License

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

REQUIRED_PACKAGES += system/library
