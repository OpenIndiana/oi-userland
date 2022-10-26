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
# Copyright 2016 Aurelien Larcher
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=     libxkbfile
COMPONENT_VERSION=  1.1.1
COMPONENT_SUMMARY=  libxkbfile - XKB file library
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:8623dc26e7aac3c5ad8a25e57b566f4324f5619e5db38457f0804ee4ed953443
COMPONENT_FMRI=     x11/library/libxkbfile

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
