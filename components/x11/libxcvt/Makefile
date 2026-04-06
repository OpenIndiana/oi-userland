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
# Copyright 2026 Andreas Wacknitz
#

X11_CATEGORY=LIB
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=     libxcvt
COMPONENT_VERSION=  0.1.3
COMPONENT_FMRI =    x11/library/libxcvt
COMPONENT_SUMMARY=  libxcvt is a library providing a standalone version of the VESA CVT standard timing modelines generator
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:a929998a8767de7dfa36d6da4751cdbeef34ed630714f2f4a767b351f2442e01
OMPONENT_ANITYA_ID=	235147
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Drop 32-bit binaries                                                                                                                                        
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRBINDIR32) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
