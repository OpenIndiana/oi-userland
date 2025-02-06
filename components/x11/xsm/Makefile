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
# Copyright 2018 Aurelien Larcher
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=         xsm
COMPONENT_VERSION=      1.0.6
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=	    xsm - X Session manager
COMPONENT_ARCHIVE=	    $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:b74cc774c6060c37592f68a90dbd31b0f2a62fb14e562769434f79be284a63ce
COMPONENT_FMRI=         x11/xsm
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
