#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Aurelien Larcher
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libglvnd
COMPONENT_VERSION=	1.3.0
COMPONENT_SUMMARY=	The GL Vendor-Neutral Dispatch library
COMPONENT_PROJECT_URL=	https://github.com/NVIDIA/libglvnd
COMPONENT_FMRI=		x11/library/libglvnd	
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  https://github.com/NVIDIA/libglvnd/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:fabf98e72e172a1402617f5daade4dd79c752a77ab1688e0c1a0ffc49605040f
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && \
                          libtoolize --automake --copy --force && \
                          aclocal && \
                          autoheader && \
                          automake -a -f -c && \
                          autoconf )

CONFIGURE_OPTIONS+= --enable-x11
CONFIGURE_OPTIONS+= --enable-glx
CONFIGURE_OPTIONS+= --enable-gles1
CONFIGURE_OPTIONS+= --enable-gles2
CONFIGURE_OPTIONS+= --enable-headers
CONFIGURE_OPTIONS+= --enable-asm
CONFIGURE_OPTIONS+= --enable-tls

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
