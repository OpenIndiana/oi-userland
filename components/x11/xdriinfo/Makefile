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

COMPONENT_NAME=     xdriinfo
COMPONENT_VERSION=  1.0.6
COMPONENT_REVISION= 1
COMPONENT_FMRI=     x11/diagnostic/xdriinfo
COMPONENT_SUMMARY=  xdriinfo - DRI drivers configuration information query utility
COMPONENT_ARCHIVE_HASH= \
  sha256:d9ccd2c3e87899417acc9ea1f3e319a4198112babe1dc711273584f607449d51

include $(WS_MAKE_RULES)/common.mk

LDFLAGS+= -L$(USRLIBDIR)/mesa/$(LIBSUBDIR) -R$(USRLIBDIR)/mesa/$(LIBSUBDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/mesa
