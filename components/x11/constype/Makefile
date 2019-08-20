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

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= constype
COMPONENT_VERSION= 1.0.4
COMPONENT_REVISION= 1
COMPONENT_FMRI= diagnostic/constype
COMPONENT_SUMMARY= constype - print type of console
COMPONENT_CLASSIFICATION= System/Hardware
COMPONENT_ARCHIVE_HASH= \
  sha256:c1848a3af93200a6db8a5905e1d9a3ca152cf4eeec4e1e7a50a8fcc6b4a0049a
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
