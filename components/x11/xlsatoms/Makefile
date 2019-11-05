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

COMPONENT_NAME=     xlsatoms
COMPONENT_VERSION=  1.1.3
COMPONENT_FMRI=     x11/diagnostic/xlsatoms
COMPONENT_SUMMARY=  xlsatoms - utility for listing atoms defined on a given X server
COMPONENT_ARCHIVE_HASH= \
  sha256:57868f958c263976727881f3078e55b86b4a109dc578d2b92f5c6d690850a382

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
