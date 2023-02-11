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
COMPONENT_VERSION=  1.0.7
COMPONENT_SUMMARY=  xdriinfo - DRI drivers configuration information query utility
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:dd838bae9d2b19ddd71fe6d30ed33abc7c85e19d223e79d35600db3fa44bf734
COMPONENT_FMRI=     x11/diagnostic/xdriinfo

include $(WS_MAKE_RULES)/common.mk

LDFLAGS+= -L$(USRLIBDIR)/mesa/$(LIBSUBDIR) -R$(USRLIBDIR)/mesa/$(LIBSUBDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/mesa
