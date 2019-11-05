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

COMPONENT_NAME=           fslsfonts
COMPONENT_VERSION=        1.0.5
COMPONENT_REVISION=       1
COMPONENT_FMRI=           x11/xfs/fslsfonts
COMPONENT_SUMMARY=  the fslsfonts utility to list fonts from an xfs font server
COMPONENT_ARCHIVE_HASH= \
  sha256:f1ed55093356b78daec2678d22f52d42ec11fe88575562d734396962e626d7f6

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libfs
