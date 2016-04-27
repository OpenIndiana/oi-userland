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
# Copyright 2015 Alexander Pyhalov (libid3tag recipe)
# Copyright 2016 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmad
COMPONENT_VERSION=	0.15.1b
IPS_COMPONENT_VERSION=	0.15.1.2
COMPONENT_SUMMARY=	MPEG Audio Decoding library from the MAD project
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_PROJECT_URL=	http://www.underbit.com/products/mad/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bbfac3ed6bfbc2823d3775ebb931087371e142bb0e9bb1bee51a76a6e0078690
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/mad/files/libmad/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download/
COMPONENT_FMRI=		library/audio/libmad
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

FP_ARCH.32 = default
FP_ARCH.64 = 64bit

CONFIGURE_OPTIONS  += --sysconfdir=/etc
CONFIGURE_OPTIONS  += --enable-shared
CONFIGURE_OPTIONS  += --disable-static
CONFIGURE_OPTIONS  += --enable-accuracy
CONFIGURE_OPTIONS  += --enable-fpm=$(FP_ARCH.$(BITS))
CONFIGURE_OPTIONS  += --enable-sso
CONFIGURE_OPTIONS  += --enable-strict-iso
# disable architecture-specific optimizations
CONFIGURE_OPTIONS  += --disable-aso

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
