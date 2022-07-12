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

COMPONENT_NAME=           xconsole
COMPONENT_VERSION=        1.0.8
COMPONENT_SUMMARY=        xconsole - monitor system console messages with X 
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_FMRI=           x11/xconsole
COMPONENT_ARCHIVE_EXTENSION= .tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:1897be35738489f92ef511caef189db8d5079469374021dc09b59e89992b7c29

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
