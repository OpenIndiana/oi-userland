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

COMPONENT_NAME=           xwininfo
COMPONENT_VERSION=        1.1.5
COMPONENT_REVISION=       1
COMPONENT_SUMMARY=        xwininfo - window information utility for X
COMPONENT_FMRI=           x11/diagnostic/xwininfo
COMPONENT_ARCHIVE_HASH= \
  sha256:7a405441dfc476666c744f5fcd1bc8a75abf8b5b1d85db7b88b370982365080e

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
