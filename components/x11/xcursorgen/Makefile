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

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           xcursorgen
COMPONENT_VERSION=        1.0.7
COMPONENT_FMRI=           image/xcursorgen
COMPONENT_CLASSIFICATION= Applications/Graphics and Imaging
COMPONENT_SUMMARY= xcursorgen - create an X cursor file from a collection of PNG images
COMPONENT_ARCHIVE_HASH= \
  sha256:35b6f844b24f1776e9006c880a745728800764dbe3b327a128772b4610d8eb3d

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
