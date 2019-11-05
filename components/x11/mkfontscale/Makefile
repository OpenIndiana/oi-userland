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

COMPONENT_NAME=     mkfontscale
COMPONENT_VERSION=  1.2.1
COMPONENT_REVISION= 1
COMPONENT_FMRI=     x11/mkfontscale
COMPONENT_SUMMARY=  mkfontscale legacy X11 scalable font metadata creation tool
COMPONENT_ARCHIVE_HASH= \
  sha256:ca0495eb974a179dd742bfa6199d561bda1c8da4a0c5a667f21fd82aaab6bac7
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --with-bzip2

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += x11/library/libfontenc
