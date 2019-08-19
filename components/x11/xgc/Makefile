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

COMPONENT_NAME=      xgc
COMPONENT_VERSION=   1.0.5
COMPONENT_REVISION=  1
COMPONENT_SUMMARY=   xgc graphics demo
COMPONENT_FMRI=      x11/xgc
COMPONENT_ARCHIVE_HASH= \
  sha256:14828d9bda358ad57efc0206bc416ee33ba542091edb186485cca5389adc2f5e
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
