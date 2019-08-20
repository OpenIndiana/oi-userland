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

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=     appres
COMPONENT_VERSION=  1.0.5
COMPONENT_REVISION= 1
COMPONENT_FMRI=     x11/appres
COMPONENT_SUMMARY=  appres - Xt application resource list utility
COMPONENT_ARCHIVE_HASH= \
  sha256:ffad893712c81943b919e3cbfe46fc65259cc0d9eb96d5e658670e3fbb265928

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxt
