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

COMPONENT_NAME=    bdftopcf
COMPONENT_VERSION= 1.1
COMPONENT_SUMMARY= bdftopcf font conversion utility
COMPONENT_FMRI=    x11/bdftopcf
COMPONENT_ARCHIVE_HASH= \
  sha256:4b4df05fc53f1e98993638d6f7e178d95b31745c4568cee407e167491fd311a2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxfont
