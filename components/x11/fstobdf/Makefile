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

COMPONENT_NAME=     fstobdf
COMPONENT_VERSION=  1.0.6
COMPONENT_REVISION= 1
COMPONENT_FMRI=     x11/xfs/fstobdf
COMPONENT_SUMMARY=  the fstobdf utility to retrieve bdf fonts from an xfs font server
COMPONENT_ARCHIVE_HASH= \
  sha256:66cf550326c993e7043f260a8ec4a533a3bf9d8f0e7397a6fe9cca803732e92e

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libfs
REQUIRED_PACKAGES += x11/library/libx11
