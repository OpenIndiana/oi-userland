#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2016 Sergey Avseyev
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=		xsel
COMPONENT_VERSION=	1.2.1
COMPONENT_SUMMARY=	A command-line program for getting and setting the contents of the X selection
COMPONENT_PROJECT_URL=	https://www.vergenet.net/~conrad/software/xsel
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:18487761f5ca626a036d65ef2db8ad9923bf61685e06e7533676c56d7d60eb14
COMPONENT_ARCHIVE_URL=	https://github.com/kfish/xsel/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         x11/xsel
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION=  ( cd $(@D) && NOCONFIGURE=1 ./autogen.sh && gmake distclean )

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
